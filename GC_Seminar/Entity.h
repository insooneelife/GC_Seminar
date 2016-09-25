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

class Message;
class World;
class Entity
{
public:

	inline unsigned int getID() const { return _id; }
	inline Vec2 getPos() const { return _pos; }
	inline void setPos(const Vec2& pos) { _pos = pos; }
	inline Vec2 getHeading() const { return _heading; }
	inline void setHeading(const Vec2& heading) { _heading = heading; }
	inline Vec2 getSide() const { return _heading.getPerp(); }
	inline float getBRadius() const { return _radius; }
	inline void setBRadius(const float radius) { _radius = radius; }

	Entity(World& world, unsigned int id, const Vec2& pos, float radius);

	virtual ~Entity();

	virtual void update();

	virtual void render();

	virtual bool handleMessage(const Message& msg);

private:

	World& _world;

	unsigned int _id;
	Vec2 _pos;
	Vec2 _heading;
	float _radius;

};