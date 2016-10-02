#include <iostream>
#include <sstream>
#include "Entity.h"
#include "GraphicsDriver.h"
#include "EntityManager.h"

Entity::Entity(World& world, unsigned int id, const Vec2& pos, float radius, Type type)
	:
	_world(world),
	_id(id),
	_pos(pos),
	_radius(radius),
	_type(type),
	_heading(1, 0),
	_is_garbage(false)
{
	EntityManager::instance->registerEntity(this);
}

Entity::~Entity()
{
	EntityManager::instance->unregisterEntity(this);
}