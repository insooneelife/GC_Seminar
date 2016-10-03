#include <iostream>
#include <sstream>
#include "Wall.h"
#include "../GraphicsDriver.h"

void Wall::render()
{
	GraphicsDriver::instance->drawLine(_begin, _end, GraphicsDriver::black);
}
