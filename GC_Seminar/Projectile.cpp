#include <iostream>
#include <sstream>
#include "Projectile.h"
#include "GraphicsDriver.h"

void Projectile::update()
{
	_pos += _heading * 15;
}

void Projectile::render()
{
	Vec2 sidev = getSide() * _radius / 2;
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos - sidev, GraphicsDriver::black);
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos + _heading * _radius * 2, GraphicsDriver::black);
	GraphicsDriver::instance->drawLine(_pos - sidev, _pos + _heading * _radius * 2, GraphicsDriver::black);
}

