#include <iostream>
#include <sstream>
#include "Entity.h"
#include "../GraphicsDriver.h"
#include "../EntityManager.h"
#include "../World.h"
#include "../PhysicsManager.h"

Entity::Entity(
	World& world,
	unsigned int id,
	const Vec2& pos,
	float radius, 
	Type type,
	const SDL_Color& color)
	:
	_world(world),
	_id(id),
	_pos(pos),
	_radius(radius),
	_type(type),
	_color(color),
	_heading(1, 0),
	_is_garbage(false),
	_body(nullptr)
{
	EntityManager::instance->registerEntity(this);
}

Entity::~Entity()
{
	EntityManager::instance->unregisterEntity(this);

	if(_body)
		_world.getPhysicsMgr()->RemoveBody(_body);
}