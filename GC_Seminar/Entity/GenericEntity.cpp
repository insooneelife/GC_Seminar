#include <iostream>
#include <sstream>
#include "GenericEntity.h"
#include "../EntityManager.h"
#include "../World.h"

GenericEntity::GenericEntity(
	World& world,
	unsigned int id,
	Type type)
	:
	_world(world),
	_id(id),
	_type(type),
	_is_garbage(false)
{
	EntityManager::instance->registerEntity(this);
}

GenericEntity::~GenericEntity()
{
	EntityManager::instance->unregisterEntity(this);
}