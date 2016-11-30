#include <iostream>
#include <sstream>
#include "GenericEntity.h"
#include "../EntityManager.h"
#include "../World.h"

GenericEntity::GenericEntity(
	World& world,
	unsigned int id,
	Type type,
	const std::string& name)
	:
	_world(world),
	_id(id),
	_type(type),
	_name(name),
	_is_garbage(false)
{
	EntityManager::instance->registerEntity(this);
}

GenericEntity::~GenericEntity()
{
	EntityManager::instance->unregisterEntity(this);
}