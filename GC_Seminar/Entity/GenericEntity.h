#pragma once
//------------------------------------------------------------------------
//
//  Name:   GenericEntity.h
//
//  Desc:   Base class for all entities in the game.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "../Math/Vec2.h"
#include "../Engine.h"
#include <Box2D/Box2D.h>

class Message;
class World;
class GenericEntity
{
public:
	enum Type
	{
		kUnit,
		kTrigger,
		kStructure,
		kUI
	};

	inline World& getWorld() const					{ return _world; }
	inline unsigned int getID() const				{ return _id; }
	inline Vec2 getPos() const						{ return _pos; }
	inline void setPos(const Vec2& pos)				{ _pos = pos; }
	inline Type getType() const						{ return _type; }
	inline bool isGarbage() const					{ return _is_garbage; }
	inline void setGarbage()						{ _is_garbage = true; }

	GenericEntity(
		World& world,
		unsigned int id,
		const Vec2& pos,
		float radius,
		Type type,
		const SDL_Color& color);

	virtual ~GenericEntity();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool handleMessage(const Message& msg) { return false; }

protected:
	World& _world;
	unsigned int _id;
	Vec2 _pos;
	Type _type;
	bool _is_garbage;
};