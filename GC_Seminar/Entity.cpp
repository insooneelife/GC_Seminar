#include <iostream>
#include "Entity.h"
#include "GraphicsDriver.h"
#include "World.h"


Entity::Entity(
	World& world,
	unsigned int id,
	const std::string& name,
	const Vec2& pos)
	:
	_world(world),
	_fsm(new Fsm()),
	_move(new Movable(*this, 1.0f, Vec2(), false)),
	_targetSys(new TargetSystem(*this, 100, 100)),
	_id(id),
	_name(name),
	_pos(pos),
	_heading(),
	_mask(kEntity),
	_is_garbage(false)
{}

void Entity::update()
{
	_fsm->visit_current_states(boost::ref(*this));

	Vec2 velocity(0.1f, 0.1f);
	_pos += velocity;
}

void Entity::render()
{
	GraphicsDriver::instance->drawCircle(_pos,  50);
	GraphicsDriver::instance->drawText("aaa", _pos);
}
