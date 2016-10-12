#include <iostream>
#include <sstream>
#include <string>
#include "Entity.h"
#include "GraphicsDriver.h"
//#include "Shapes\Shape.h"

Entity::Entity(World& world, unsigned int id, const Vec2& pos)
	:
	_world(world),
	_id(id),
	_pos(pos)
{}

Entity::~Entity()
{
}

void Entity::update()
{
	
}

void Entity::render()
{
	std::stringstream ss;
	ss << _id;
	GraphicsDriver::instance->drawText(ss.str().c_str(), _pos, GraphicsDriver::blue);
}
