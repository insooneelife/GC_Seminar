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
#include "../Entity/GenericEntity.h"
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
		bool sensor,
		float radius,
		GenericEntity::Type owner_type);

	inline b2Body* getBody() const { return _body; }
	inline float getBRadius() const { return _radius; }
	inline GenericEntity::Type getOwnerType() const { return _owner_type; }

	CollisionComponent::CollisionComponent(
		ICollisionComponent& owner,
		b2Body* body,
		float radius,
		GenericEntity::Type type)
		:
		_owner(owner),
		_body(body),
		_radius(radius),
		_owner_type(type)
	{}

	~CollisionComponent()
	{
		if(_body)
			_body->GetWorld()->DestroyBody(_body);
	}

protected:
	ICollisionComponent& _owner;
	b2Body* _body;
	float _radius;
	GenericEntity::Type _owner_type;
};