#include <iostream>
#include "Rect.h"
#include "../GraphicsDriver.h"

bool Rect::collide(const Shape* const other) const
{
	return other->collide(this);
}

bool Rect::collide(const Rect* const other) const
{
	return Shape::collide(this, other);
}

bool Rect::collide(const Circle* const other) const
{
	return Shape::collide(this, other);
}

void Rect::render()
{
	GraphicsDriver::instance->drawLine(getTopLeft(), getBottomLeft(), GraphicsDriver::blue);
	GraphicsDriver::instance->drawLine(getBottomLeft(), getBottomRight(), GraphicsDriver::blue);
	GraphicsDriver::instance->drawLine(getBottomRight(), getTopRight(), GraphicsDriver::blue);
	GraphicsDriver::instance->drawLine(getTopRight(), getTopLeft(), GraphicsDriver::blue);
}