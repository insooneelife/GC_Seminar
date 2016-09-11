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

	Entity(World& world, const Vec2& pos);

	virtual void update();

	virtual void render();

private:

	Vec2 _pos;

	World& _world;
};