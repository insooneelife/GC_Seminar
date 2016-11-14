#pragma once

//-----------------------------------------------------------------------------
//
//  Name:   Trigger.h
//
//  Author: Insub Im (insooneelife@naver.com)
//
//  Desc:   Base class for a trigger.
//			A trigger is an object that is
//          activated when an entity moves within its region of influence.
//
//-----------------------------------------------------------------------------
#include <memory>
#include "../Entity.h"
#include "../../GraphicsDriver.h"
#include "../../World.h"

class Message;
class World;

class Trigger : public Entity
{
public:
	Trigger::Trigger(World& world, unsigned int id, const Vec2& pos)
		:
		Entity(world, id, pos, 20.0f, Entity::Type::kTrigger, GraphicsDriver::black),
		_active(true)
	{
		b2CircleShape shape;
		shape.m_radius = _radius;

		_body = _world.getPhysicsMgr()->CreateBody(
			_pos.x, _pos.y, b2BodyType::b2_staticBody, &shape, true);
		_body->SetUserData(this);
	}

	virtual ~Trigger() {}
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool handleMessage(const Message& msg) { return false; }

	inline bool isActive() { return _active; }

protected:

	inline void setInactive() { _active = false; }
	inline void setActive() { _active = true; }

private:

	//it's convenient to be able to deactivate certain types of triggers
	//on an event. Therefore a trigger can only be triggered when this
	//value is true (respawning triggers make good use of this facility)
	bool _active;
};

