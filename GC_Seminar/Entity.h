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
//#include "Shapes\Shape.h"

class Shape;
class World;
class Entity
{
public:

	inline unsigned int getID() const { return _id; }
	inline Vec2 getPos() const { return _pos; }
	inline Shape* getBody() const { return _body; }

	Entity(World& world, unsigned int id, const Vec2& pos, Shape* const shape);
	~Entity();

	virtual void update();
	virtual void render();

private:

	unsigned int _id;

	Vec2 _pos;

	World& _world;

	Shape* _body;
	
};