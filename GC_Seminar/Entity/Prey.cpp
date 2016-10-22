#include <iostream>
#include <sstream>
#include "Prey.h"
#include "../GraphicsDriver.h"

Prey::Prey(World& world, unsigned int id, const Vec2& pos)
	:
	Entity(world, id, pos, 0.20f, Entity::Type::kPrey, GraphicsDriver::black)
{}

void Prey::render()
{
	GraphicsDriver::instance->drawCircle(_pos, _radius, _color);
}

