#include <iostream>
#include <sstream>
#include "CollisionComponent.h"

CollisionComponent* CollisionComponent::create(
	b2World* world,
	ICollisionComponent* owner,
	b2Shape* shape,
	b2BodyType type,
	Vec2 pos,
	bool sensor)
{
	b2BodyDef bd;
	bd.position.Set(pos.x, pos.y);
	bd.type = type;
	bd.allowSleep = false;
	b2Body* body = world->CreateBody(&bd);

	b2FixtureDef fd;
	fd.shape = shape;
	fd.density = 20.0f;
	fd.friction = 1.0f;
	fd.restitution = 0.0f;
	fd.isSensor = sensor;
	body->CreateFixture(&fd);
	body->SetLinearDamping(2.0f);
	body->SetUserData(owner);

	return new CollisionComponent(*owner, body);
}


