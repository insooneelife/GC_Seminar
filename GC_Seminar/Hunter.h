#pragma once
//------------------------------------------------------------------------
//
//  Name:   Hunter.h
//
//  Desc:   The entity which intakes other entities and grows bigger.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "Entity.h"

class Hunter : public Entity
{
public:
	enum State
	{
		kIdle,
		kMoving
	};

	void enterMovingState(const Vec2& desti);

	virtual ~Hunter() {}
	virtual void update();
	virtual void render();

	Hunter(World& world, unsigned int id, const Vec2& pos)
		:
		Entity(world, id, pos, 25.0f, Entity::Type::kHunter),
		_state(kIdle)
	{}

private:
	State _state;
	Vec2 _destination;
};