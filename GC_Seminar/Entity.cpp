#include <iostream>
#include <sstream>
#include <string>
#include "Entity.h"
#include "GraphicsDriver.h"
#include "Shapes\Shape.h"

Entity::Entity(World& world, unsigned int id, const Vec2& pos, Shape* const shape)
	:
	_world(world),
	_id(id),
	_pos(pos),
	_body(shape)
	{}

Entity::~Entity()
{
	if (_body)
		delete _body;
}

void Entity::update()
{
	
}

void Entity::render()
{
	_body->render();

	std::stringstream ss;
	ss << _id;
	GraphicsDriver::instance->drawText(ss.str().c_str(), _pos, GraphicsDriver::blue);
}
