#include <iostream>
#include <sstream>
#include "Projectile.h"
#include "../GraphicsDriver.h"
#include "../PhysicsManager.h"
#include "../World.h"

namespace
{
	const int kDefaultLifeTime = 50;

	const float kProjectileRenderRadius = 0.15f;
	const float kProjectileBodyRadius = 0.10f;
}

Projectile::Projectile(
	World& world,
	unsigned int id,
	unsigned int owner_id,
	const Vec2& pos,
	const Vec2& heading,
	int proj_speed)
	:
	Entity(world, id, pos, kProjectileRenderRadius, Entity::Type::kProjectile, GraphicsDriver::black),
	_owner_id(owner_id),
	_life_time(kDefaultLifeTime),
	_proj_speed(proj_speed)
{
	setHeading(heading);

	b2CircleShape shape;
	shape.m_radius = kProjectileBodyRadius;

	_body = _world.getPhysicsMgr()->CreateBody(_pos.x, _pos.y, b2BodyType::b2_dynamicBody, &shape, false);
	
	Vec2 velocity = _heading * (float)_proj_speed;
	_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
	_body->SetUserData(this);
}

void Projectile::update()
{
	if (_life_time-- < 0)
		_is_garbage = true;

	_pos.set(_body->GetPosition().x, _body->GetPosition().y);
}

void Projectile::render()
{
	Vec2 sidev = getSide() * _radius * 0.5f;
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos - sidev, _color);
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos + _heading * _radius * 2, _color);
	GraphicsDriver::instance->drawLine(_pos - sidev, _pos + _heading * _radius * 2, _color);
}

