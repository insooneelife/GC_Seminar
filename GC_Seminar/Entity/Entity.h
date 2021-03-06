#pragma once
//------------------------------------------------------------------------
//
//  Name:   Entity.h
//
//  Desc:   Base class for all entities in the game.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "../Math/Vec2.h"
#include "../Engine.h"
#include <Box2D\Box2D.h>

class Message;
class World;
class Entity
{
public:
	enum Type
	{
		kHunter,
		kPrey,
		kProjectile,
		kTrigger,
		kStructure,
		kButton
	};

	inline World& getWorld() const					{ return _world; }
	inline unsigned int getID() const				{ return _id; }
	inline Vec2 getPos() const						{ return _pos; }
	inline void setPos(const Vec2& pos)				{ _pos = pos; }
	inline Vec2 getHeading() const					{ return _heading; }
	inline void setHeading(const Vec2& heading)		{ _heading = heading; }
	inline Vec2 getSide() const						{ return _heading.getPerp(); }
	inline float getBRadius() const					{ return _radius; }
	inline void setBRadius(const float radius)		{ _radius = radius; }
	inline Type getType() const						{ return _type; }
	inline bool isGarbage() const					{ return _is_garbage; }
	inline void setGarbage()						{ _is_garbage = true; }
	inline SDL_Color getColor() const				{ return _color; }
	inline void setColor(const SDL_Color& color)	{ _color = color; }
	
	inline b2Body* getBody() const					{ return _body; }

	Entity(
		World& world,
		unsigned int id,
		const Vec2& pos,
		float radius,
		Type type,
		const SDL_Color& color);

	virtual ~Entity();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool handleMessage(const Message& msg) { return false; }

protected:
	World& _world;
	unsigned int _id;
	Vec2 _pos;
	Vec2 _heading;
	float _radius;
	Type _type;
	bool _is_garbage;
	SDL_Color _color;

	b2Body* _body;
};