#include <iostream>
#include "Entity.h"
#include "GraphicsDriver.h"

Entity::Entity(World& world, const Vec2& pos)
	:
	_world(world),
	_pos(pos)
	{}

void Entity::update()
{
	Vec2 velocity(0.1f, 0.1f);
	_pos += velocity;
}

void Entity::render()
{
	GraphicsDriver::instance->drawCircle(_pos,  50);
	GraphicsDriver::instance->drawText("aaa", _pos);
}
