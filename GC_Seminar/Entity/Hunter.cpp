#include <iostream>
#include <sstream>
#include "Hunter.h"
#include "../EntityManager.h"
#include "../GraphicsDriver.h"
#include "../PhysicsManager.h"
#include "../World.h"

Hunter::Hunter(World& world, unsigned int id, const Vec2& pos)
	:
	Entity(world, id, pos, 0.25f, Entity::Type::kHunter, GraphicsDriver::black),
	_state(kIdle),
	_experience(5),
	_hp(100),
	_damage(10),
	_proj_speed(15),
	_is_player(true)
{
	b2CircleShape shape;
	shape.m_radius = 0.2f;

	_body = _world.getPhysicsMgr()->CreateApplyForceBody(_pos.x, _pos.y, &shape);
	_body->SetUserData(this);
}

Hunter::~Hunter()
{}

bool Hunter::upgradeDamage()
{
	int cost = 10;
	if (_experience - cost < 0)
		return false;

	setExp(getExp() - cost);
	_damage += 1;

	std::cout << "upgrade damage to : " << _damage << std::endl;
	return true;
}

bool Hunter::upgradeRange()
{
	int cost = 10;
	if (_experience - cost < 0)
		return false;

	setExp(getExp() - cost);
	_proj_speed += 1;

	std::cout << "upgrade range to : " << _proj_speed << std::endl;
	return true;
}

void Hunter::enterMovingState(const Vec2& desti)
{
	_destination = desti;
	_state = State::kMoving;
}

void Hunter::takeDamage(int damage, unsigned int who)
{
	_hp = std::max(0, _hp - damage);
	if (_hp == 0)
	{
		setGarbage();
		int expr = 10;
		EntityManager::instance->dispatchMsg(_id, who, Message::MsgType::kIncrease, &expr);
	}
		
}

void Hunter::update()
{
	if (_state == State::kIdle)
	{}
	else if (_state == State::kMoving)
	{
		float speed = 10;
		float expect_radius = 0.25f;

		Vec2 velocity = (_destination - _pos).getNormalized() * speed;
		
		_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
		
		
		if (_pos.distance(_destination) < expect_radius)
			_state = State::kIdle;
	}
	_pos.set(_body->GetPosition().x, _body->GetPosition().y);
}

void Hunter::render()
{
	std::stringstream ss;
	ss << _id;
	
	GraphicsDriver::instance->drawCircle(_pos, _radius, _color);
	GraphicsDriver::instance->drawText(ss.str(), _pos);

	Vec2 sidev = getSide() * _radius / 2;
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos - sidev, _color);
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos + _heading * _radius * 2, _color);
	GraphicsDriver::instance->drawLine(_pos - sidev, _pos + _heading * _radius * 2, _color);
}


bool Hunter::handleMessage(const Message& msg) 
{
	switch (msg.getMsg())
	{
	case Message::kDamage:
		takeDamage(Message::voidToType<int>(msg.getExtraInfo()), msg.getSender());
		break;

	case Message::kIncrease:
		setExp(getExp() + Message::voidToType<int>(msg.getExtraInfo()));
		break;

	case Message::kDecrease:
		setExp(getExp() - 1);
		break;

	default:
		break;
	}
	return false; 
}