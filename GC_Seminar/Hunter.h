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

	inline int getIntake() const		{ return _intake; }
	inline void increase(int intake)	{ _radius += 0.5f * (float)intake; _intake += intake; }
	inline void decrease()				{ _radius--; _intake--; }

	Hunter(World& world, unsigned int id, const Vec2& pos)
		:
		Entity(world, id, pos, 25.0f, Entity::Type::kHunter),
		_state(kIdle),
		_intake(5)
	{}

	void enterMovingState(const Vec2& desti);

	virtual ~Hunter() {}
	virtual void update();
	virtual void render();

private:
	State _state;
	Vec2 _destination;
	int _intake;
};