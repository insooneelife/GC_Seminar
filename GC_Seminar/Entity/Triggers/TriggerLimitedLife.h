#pragma once

//-----------------------------------------------------------------------------
//
//  Name:     TriggerLimitedLife.h
//
//  Author:   Insub Im
//
//  Desc:     Defines a trigger that only remains in the game for a specified
//            number of update steps.
//
//-----------------------------------------------------------------------------

#include "Trigger.h"

class TriggerLimitedLife : public Trigger
{
public:

	TriggerLimitedLife(
		World& world,
		unsigned int id,
		const Vec2& pos,
		int life_time)
		:
		Trigger(world, id, pos),
		_life_time(life_time)
	{}

	virtual ~TriggerLimitedLife() override
	{}

	virtual void update() override
	{
		// If the lifetime counter expires set this trigger
		// to be removed from the game.
		if (--_life_time <= 0)
		{
			setGarbage();
		}
	}

	virtual void render() override {};
	virtual bool handleMessage(const Message& msg) override { return false; }

protected:

	// The lifetime of this trigger in update-steps
	int _life_time;
};
