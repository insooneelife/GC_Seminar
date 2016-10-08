#include <iostream>
#include "Circle.h"
#include "../GraphicsDriver.h"

bool Circle::collide(const Shape* const other) const
{
	return other->collide(this);
}

bool Circle::collide(const Rect* const other) const
{
	return Shape::collide(this, other);
}

bool Circle::collide(const Circle* const other) const
{
	return Shape::collide(this, other);
}

void Circle::render()
{
	GraphicsDriver::instance->drawCircle(_center, _radius, 15.0f, GraphicsDriver::blue);
}