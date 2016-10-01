#include <iostream>
#include <sstream>
#include "Hunter.h"
#include "GraphicsDriver.h"

void Hunter::update()
{}

void Hunter::render()
{
	std::stringstream ss;
	ss << _id;
	GraphicsDriver::instance->drawCircle(_pos, _radius, GraphicsDriver::black);
	GraphicsDriver::instance->drawText(ss.str(), _pos);
	GraphicsDriver::instance->drawLine(_pos, _pos + _heading * _radius * 2, GraphicsDriver::black);
	GraphicsDriver::instance->drawCircle(_pos + _heading * _radius * 2, _radius / 2, GraphicsDriver::white);
}

