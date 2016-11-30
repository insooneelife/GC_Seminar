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
#include "Entity.h"
#include "../GraphicsDriver.h"
#include "../World.h"
#include "../MessageData.h"

class Message;
class World;

class Trigger : public Entity
{
public:
	enum Condition
	{
		kCollision, kMessage, kTimer
	};

	static Trigger* createCreateEntityTrigger(
		World& world,
		unsigned int id,
		Vec2 pos,
		int condition,
		int create_entity_type,
		int create_entity_breed,
		float wait_time);

	Trigger(
		World& world,
		unsigned int id,
		const Vec2& pos,
		Condition condition);

	virtual ~Trigger() {}
	virtual void update() {}
	virtual void render() override;
	virtual bool handleMessage(const Message& msg);

	void activateOneSelf(Entity& activator);

	inline bool isActive() const { return _active; }
	inline void setInactive() { _active = false; }
	inline void setActive() { _active = true; }
	inline Condition getCondition() const { return _condition; }

	void pushMessage(MessageData* msg)
	{
		_messages.emplace_back(msg);
	}


private:

	bool _active;
	Condition _condition;
	std::vector<std::unique_ptr<MessageData>> _messages;
};

