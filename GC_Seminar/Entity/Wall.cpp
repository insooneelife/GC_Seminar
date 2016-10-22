#include <iostream>
#include <sstream>
#include "Wall.h"
#include "../GraphicsDriver.h"
#include "../World.h"
#include "../PhysicsManager.h"

Wall::Wall(
	World& world,
	unsigned int id,
	const Vec2& begin,
	const Vec2& end,
	const Vec2& heading)
	:
	Entity(world, id, (begin + end) / 2, 0.0f, Entity::Type::kWall, GraphicsDriver::black),
	_begin(begin),
	_end(end)
{
	setHeading(heading);

	auto physics = _world.getPhysicsMgr()->GetPhysicsWorld();

	b2BodyDef bd;
	_body = physics->CreateBody(&bd);

	b2EdgeShape shape;
	shape.Set(b2Vec2(_begin.x, _begin.y), b2Vec2(_end.x, _end.y));
	_body->CreateFixture(&shape, 0.0f);
	_body->SetUserData(this);
}

void Wall::render()
{
	GraphicsDriver::instance->drawLine(_begin, _end, _color);
}
