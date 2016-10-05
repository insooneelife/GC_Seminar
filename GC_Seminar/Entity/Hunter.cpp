#include <iostream>
#include <sstream>
#include "Hunter.h"
#include "../EntityManager.h"
#include "../GraphicsDriver.h"

Hunter::Hunter(World& world, unsigned int id, const Vec2& pos)
	:
	Entity(world, id, pos, 25.0f, Entity::Type::kHunter, GraphicsDriver::black),
	_state(kIdle),
	_intake(5),
	_hp(100),
	_damage(10),
	_proj_speed(15)
{}

bool Hunter::upgradeDamage()
{
	int cost = 10;
	if (_intake - cost < 0)
		return false;

	_intake -= cost;
	_damage += 1;

	std::cout << "upgrade damage to : " << _damage << std::endl;
}

bool Hunter::upgradeRange()
{
	int cost = 10;
	if (_intake - cost < 0)
		return false;

	_intake -= cost;
	_proj_speed += 1;

	std::cout << "upgrade range to : " << _proj_speed << std::endl;
}

void Hunter::enterMovingState(const Vec2& desti)
{
	_destination = desti;
	_state = State::kMoving;
}

void Hunter::takeDamage(int damage)
{
	_hp = std::max(0, _hp - damage);
	if (_hp == 0)
		setGarbage();
}

void Hunter::update()
{
	if (_state == State::kIdle)
	{}
	else if (_state == State::kMoving)
	{
		float speed = 6.0f;
		float expect_radius = 10.0f;
		_pos += (_destination - _pos).getNormalized() * speed;

		if (_pos.distance(_destination) < expect_radius)
			_state = State::kIdle;
	}
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
		takeDamage(Message::voidToType<int>(msg.getExtraInfo()));
		break;

	case Message::kIncrease:
		increase(Message::voidToType<int>(msg.getExtraInfo()));
		break;

	case Message::kDecrease:
		decrease();
		break;

	default:
		break;
	}
	return false; 
}
