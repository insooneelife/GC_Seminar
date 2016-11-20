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
#include "../Components/Interfaces.h"
#include <Box2D/Box2D.h>

class Message;
class World;
class GenericEntity : public IMessageHandler
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
	inline Type getType() const						{ return _type; }
	inline bool isGarbage() const					{ return _is_garbage; }
	inline void setGarbage()						{ _is_garbage = true; }

	GenericEntity(
		World& world,
		unsigned int id,
		Type type);

	virtual unsigned int getID() const override { return _id; }

	virtual ~GenericEntity();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool handleMessage(const Message& msg) { return false; }

protected:
	World& _world;
	unsigned int _id;
	Type _type;
	bool _is_garbage;
};