#pragma once

//-----------------------------------------------------------------------------
//
//  Name:     TriggerByCondition.h
//
//  Author:   Insub Im
//
//
//-----------------------------------------------------------------------------

#include "Trigger.h"
#include "../../Utils.h"

class TriggerByCondition : public Trigger
{
public:

	TriggerByCondition(
		World& world,
		unsigned int id,
		const Vec2& pos)
		:
		Trigger(world, id, pos)
	{}

	virtual ~TriggerByCondition() override
	{}

	//this is called each game-tick to update the trigger's internal state
	virtual void update() override
	{}

	virtual void render() override {}
	virtual bool handleMessage(const Message& msg) override	{ return true; }


protected:

	
};


