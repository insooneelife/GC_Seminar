#include <iostream>
#include <sstream>
#include "Entity.h"
#include "GraphicsDriver.h"
#include "EntityManager.h"

Entity::Entity(World& world, unsigned int id, const Vec2& pos, float radius)
	:
	_world(world),
	_id(id),
	_pos(pos),
	_radius(radius),
	_heading(1, 0)
	{}

void Entity::update()
{}

void Entity::render()
{
	std::stringstream ss;
	ss << _id;
	GraphicsDriver::instance->drawCircle(_pos, _radius);
	GraphicsDriver::instance->drawText(ss.str(), _pos);
	GraphicsDriver::instance->drawLine(_pos, _pos + _heading * _radius * 2);
}

bool Entity::handleMessage(const Message& msg) 
{
	return false; 
}