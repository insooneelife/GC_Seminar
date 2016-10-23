#include <iostream>
#include <sstream>
#include "Prey.h"
#include "../GraphicsDriver.h"
#include "../World.h"
#include "../PhysicsManager.h"

namespace
{
	const float kPreyRenderRadius = 0.20f;
	const float kPreyBodyRadius = 0.15f;
}

Prey::Prey(World& world, unsigned int id, const Vec2& pos)
	:
	Entity(world, id, pos, kPreyRenderRadius, Entity::Type::kPrey, GraphicsDriver::black)
{
	b2CircleShape shape;
	shape.m_radius = kPreyBodyRadius;

	_body = _world.getPhysicsMgr()->CreateBody(_pos.x, _pos.y, b2BodyType::b2_dynamicBody, &shape, false);
	_body->SetUserData(this);
}

void Prey::render()
{
	GraphicsDriver::instance->drawCircle(_pos, _radius, _color);
}

