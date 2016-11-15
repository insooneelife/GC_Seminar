#include <iostream>
#include <sstream>
#include <cassert>
#include "Trigger.h"
#include "../Entity/Hunter.h"
#include "../World.h"
#include "../GraphicsDriver.h"
#include "../EntityManager.h"
#include "../MessageData.h"
#include "../Utils.h"

Trigger* Trigger::createCreateEntityTrigger(
	World& world,
	unsigned int id,
	Vec2 pos,
	int condition,
	int create_entity_type,
	int create_entity_breed,
	float wait_time)
{
	auto trigger = new Trigger(world, id, pos, (Condition)condition);

	trigger->pushMessage(new CreateEntityData(
		CreateEntityData::Member(id, create_entity_type, create_entity_breed, wait_time)));

	trigger->pushMessage(new ActivateTriggerData(ActivateTriggerData::Member(wait_time)));

	if (condition == Trigger::Condition::kTimer)
		trigger->activateOneSelf(*trigger);

	return trigger;
}


Trigger::Trigger(
	World& world,
	unsigned int id,
	const Vec2& pos,
	Condition condition)
	:
	Entity(world, id, pos, 2.0f, Entity::Type::kTrigger, GraphicsDriver::black),
	_active(false),
	_condition(condition)
{
	b2CircleShape shape;
	shape.m_radius = _radius;

	_body = _world.getPhysicsMgr()->CreateBody(
		_pos.x, _pos.y, b2BodyType::b2_staticBody, &shape, true);
	_body->SetUserData(this);
}

void Trigger::render()
{
	std::stringstream ss;
	ss << _id;
	GraphicsDriver::instance->drawText("trigger" + ss.str(), _pos);
}

bool Trigger::handleMessage(const Message& msg) 
{
	switch (msg.getMsg())
	{
	case Message::kActivateTrigger:

		MessageData* msgData = static_cast<MessageData*>(msg.getExtraInfo());

		if (msgData->type == MessageData::kActivateTrigger)
		{
			auto data = static_cast<ActivateTriggerData*>(msgData);
			Entity* ent = EntityManager::instance->getEntity(data->param.target_id);

			if (ent)
			{
				Trigger* trg = static_cast<Trigger*>(ent);
				trg->activateOneSelf(*this);
			}
		}
		else if (msgData->type == MessageData::kCreateEntity)
		{
			auto data = static_cast<CreateEntityData*>(msgData);
		
			if (data->member.entity_type == Entity::kHunter)
			{
				_world.createHunter(Vec2(data->param.x, data->param.y) + Vec2(random(-0.5f,0.5f), random(-0.5f, 0.5f)));
			}
		}
		else if (msgData->type == MessageData::kHealEntity)
		{
			auto data = static_cast<HealEntityData*>(msgData);
			std::cout
				<< "healer_id : " << data->member.healer_id << " "
				<< "heal_hp : " << data->member.heal_hp << " "
				<< "target_id : " << data->param.target_id << " "
				<< "type : " << data->type << " "
				<< std::endl;
		}
		else if (msgData->type == MessageData::kMoveEntity)
		{
			auto data = static_cast<MoveEntityData*>(msgData);
			std::cout
				<< "targetId : " << data->param.target_id << " "
				<< "type : " << data->type << " "
				<< "pos : " << data->member.destX << " " << data->member.destY
				<< std::endl;
		}

		break;
	}
	return false;
}


void Trigger::activateOneSelf(Entity& activator)
{
	float wait_time = 0.1f;
	void* message_data = nullptr;

	for (auto i = std::begin(_messages); i != std::end(_messages); ++i)
	{
		std::cout << "activate";
		if ((*i)->type == MessageData::kActivateTrigger)
		{
			ActivateTriggerData* data = static_cast<ActivateTriggerData*>(i->get());
			data->setParam(ActivateTriggerData::Param(activator.getID()));
			wait_time = data->member.wait_time;
			message_data = data;
		}
		else if ((*i)->type == MessageData::kCreateEntity)
		{
			CreateEntityData* data = static_cast<CreateEntityData*>(i->get());
			data->setParam(CreateEntityData::Param(_pos.x, _pos.y));
			wait_time = data->member.wait_time;
			message_data = data;
		}
		else if ((*i)->type == MessageData::kHealEntity)
		{
			HealEntityData* data = static_cast<HealEntityData*>(i->get());
			data->setParam(HealEntityData::Param(activator.getID()));
			message_data = data;
		}
		else if ((*i)->type == MessageData::kMoveEntity)
		{
			MoveEntityData* data = static_cast<MoveEntityData*>(i->get());
			data->setParam(MoveEntityData::Param(activator.getID()));
			message_data = data;
		}
		else
		{
			assert(false && "invalid message type");
		}

		EntityManager::instance->dispatchMsg(
			wait_time,
			_id, _id, Message::kActivateTrigger,
			message_data);
	}
}
