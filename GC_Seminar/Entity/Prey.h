#pragma once
//------------------------------------------------------------------------
//
//  Name:   Prey.h
//
//  Desc:   The entity which hunter intakes.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "Entity.h"

class Prey : public Entity
{
public:
	virtual ~Prey() {}
	virtual void update() {}
	virtual void render();

	Prey(World& world, unsigned int id, const Vec2& pos)
		:
		Entity(world, id, pos, 10.0f, Entity::Type::kPrey)
	{}
};