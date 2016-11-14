#pragma once

//-----------------------------------------------------------------------------
//
//  Name:     TriggerRespawning.h
//
//  Author:   Insub Im
//
//  Desc:     Base class to create a trigger that is capable of respawning
//            after a period of inactivity.
//
//-----------------------------------------------------------------------------

#include "Trigger.h"
#include "../../Utils.h"

class TriggerRespawning : public Trigger
{
public:

	TriggerRespawning(
		World& world,
		unsigned int id,
		const Vec2& pos)
		:
		Trigger(world, id, pos),
		_num_update_for_respawn(0),
		_num_update_remaining(random(0, 50))
	{}

	virtual ~TriggerRespawning() override
	{}

	//this is called each game-tick to update the trigger's internal state
	virtual void update() override
	{
		if (!isActive() && (_num_update_remaining-- <= 0))
		{
			setActive();
		}
	}

	virtual void render() override {}
	virtual bool handleMessage(const Message& msg) override	{ return true; }

	void setRespawnDelay(unsigned int num_ticks)
	{
		_num_update_for_respawn = num_ticks;
	}

protected:

	//When a bot comes within this trigger's area of influence it is triggered
	//but then becomes INACTIVE for a specified amount of time. These values
	//control the amount of time required to pass before the trigger becomes 
	//ACTIVE once more.
	int   _num_update_for_respawn;
	int   _num_update_remaining;

	//sets the trigger to be INACTIVE for _num_update_for_respawn 
	//update-steps
	void deactivate()
	{
		setInactive();
		_num_update_remaining = _num_update_for_respawn;
	}
};


