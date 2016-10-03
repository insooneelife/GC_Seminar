#include <iostream>
#include <sstream>
#include "Prey.h"
#include "GraphicsDriver.h"

void Prey::render()
{
	GraphicsDriver::instance->drawCircle(_pos, _radius, GraphicsDriver::black);
}

