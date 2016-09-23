#include <iostream>
#include <sstream>
#include "Entity.h"
#include "GraphicsDriver.h"

Entity::Entity(World& world, const Vec2& pos, unsigned int id)
	:
	_world(world),
	_pos(pos),
	_heading(1, 0),
	_id(id)
	{}

void Entity::update()
{}

void Entity::render()
{
	std::stringstream ss;
	ss << _id;
	GraphicsDriver::instance->drawCircle(_pos,  50);
	GraphicsDriver::instance->drawText(ss.str(), _pos);
	GraphicsDriver::instance->drawLine(_pos, _pos + _heading * 100);
}
