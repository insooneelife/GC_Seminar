#include <iostream>
#include <sstream>
#include "Projectile.h"
#include "../GraphicsDriver.h"

Projectile::Projectile(
	World& world,
	unsigned int id,
	unsigned int owner_id,
	const Vec2& pos,
	const Vec2& heading,
	int proj_speed)
	:
	Entity(world, id, pos, 15.0f, Entity::Type::kProjectile, GraphicsDriver::black),
	_owner_id(owner_id),
	_life_time(50),
	_proj_speed(proj_speed)
{
	setHeading(heading);
}

void Projectile::update()
{
	if (_life_time-- < 0)
		_is_garbage = true;

	

	_pos += _heading * (float)_proj_speed;
}

void Projectile::render()
{
	Vec2 sidev = getSide() * _radius / 2;
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos - sidev, _color);
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos + _heading * _radius * 2, _color);
	GraphicsDriver::instance->drawLine(_pos - sidev, _pos + _heading * _radius * 2, _color);
}

