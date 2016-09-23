//------------------------------------------------------------------------
//
//  Name:   Entity.h
//
//  Desc:   Base class for all entities in the game.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#pragma once

#include "Math\Vec2.h"
#include "Engine.h"

class World;
class Entity
{
public:

	inline Vec2 getPos() const { return _pos; }
	inline Vec2 getHeading() const { return _heading; }
	inline void setHeading(const Vec2& heading) { _heading = heading; }

	Entity(World& world, const Vec2& pos, unsigned int id);

	virtual void update();

	virtual void render();

private:

	World& _world;

	Vec2 _pos;
	Vec2 _heading;

	unsigned int _id;
};