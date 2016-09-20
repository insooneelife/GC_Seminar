#include <iostream>
#include "Entity.h"
#include "GraphicsDriver.h"
#include "World.h"
#include "EntityManager.h"

Entity* Entity::createUnit(World& world, const Vec2& pos)
{
	unsigned int id = EntityManager::instance->genID();

	std::stringstream ss;
	ss << id;
	std::string name = "unit" + ss.str();

	const float bounding_radius = 15;
	const float move_speed = 1.0f;
	const float attack_range = 50;
	const float view_range = 300;
	const int max_hp = 100;
	const int damage = 10;
	const int attackFrameDelay = 1;

	Entity* ent = new Entity(world, id, name, pos, bounding_radius, kEntity);
	Fsm* fsm = new Fsm();
	Movable* move = new Movable(*ent, move_speed, Vec2(), false);
	TargetSystem* targetSys = new TargetSystem(*ent, attack_range, view_range);
	Hittable* hit = new Hittable(*ent, max_hp);
	AttackSystem* attack = new MeleeAttack(*ent, damage, attackFrameDelay);

	ent->setFsm(fsm);
	ent->setMove(move);
	ent->setTargetSys(targetSys);
	ent->setHittable(hit);
	ent->setAttackSys(attack);
	return ent;
}

Entity* Entity::createStructure(World& world, const Vec2& pos)
{
	unsigned int id = EntityManager::instance->genID();

	std::stringstream ss;
	ss << id;
	std::string name = "structure" + ss.str();
	const float bounding_radius = 35;

	Entity* ent = new Entity(world, id, name, pos, bounding_radius, kStructure);

	return ent;
}

Entity::Entity(
	World& world,
	unsigned int id,
	const std::string& name,
	const Vec2& pos,
	float bounding_radius,
	int type)
	:
	// Data
	_world(world),
	_id(id),
	_name(name),
	_pos(pos),
	_bounding_radius(bounding_radius),
	_type(type),
	_heading(),
	_is_garbage(false),
	_alive(true),
	
	// Components
	_fsm(nullptr),
	_move(nullptr),
	_targetSys(nullptr),
	_hit(nullptr),
	_attackSys(nullptr)
{
	EntityManager::instance->registerEntity(this);
}

Entity::~Entity()
{
	EntityManager::instance->unregisterEntity(this);
}

void Entity::update()
{
	if(_fsm)
		_fsm->visit_current_states(boost::ref(*this));
	//

}

void Entity::render()
{
	GraphicsDriver::instance->drawCircle(_pos, _bounding_radius, GraphicsDriver::black);
	GraphicsDriver::instance->drawText(_name , _pos, GraphicsDriver::blue);
	
	if(_fsm)
		GraphicsDriver::instance->drawText(
			stateToString(*_fsm), _pos + Vec2(0, 20), GraphicsDriver::blue);
	
	if(_hit)
		_hit->render();

	if(_targetSys)
		_targetSys->render();
}


bool Entity::handleMessage(const Message& msg)
{
	switch (msg.getMsg())
	{
	case Message::MsgType::None:
	{
		return true;
	}
	case Message::MsgType::Damage:
	{
		// For Structures
		if (!_hit)
			return true;

		int damage = Message::voidToType<int>(msg.getExtraInfo());
		_hit->takeDamaged(damage);
		return true;
	}
	break;
	}

	return false;
}