#pragma once
//------------------------------------------------------------------------
//
//  Name:   CollisionComponent.h
//
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "../Math/Vec2.h"
#include "../Engine.h"
#include <Box2D/Box2D.h>

class ICollisionComponent;
class Message;
class World;
class CollisionComponent
{
public:
	static CollisionComponent* create(
		b2World* world,
		ICollisionComponent* owner,
		b2Shape* shape,
		b2BodyType type,
		Vec2 pos,
		bool sensor);

	inline b2Body* getBody() const { return _body; }

	CollisionComponent::CollisionComponent(ICollisionComponent& owner, b2Body* body)
		:
		_owner(owner),
		_body(body)
	{}

	~CollisionComponent()
	{
		if(_body)
			_body->GetWorld()->DestroyBody(_body);
	}

protected:
	ICollisionComponent& _owner;
	b2Body* _body;
};