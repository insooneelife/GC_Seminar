#include <iostream>
#include <sstream>
#include "Hunter.h"
#include "../GraphicsDriver.h"

void Hunter::enterMovingState(const Vec2& desti)
{
	_destination = desti;
	_state = State::kMoving;
}

void Hunter::update()
{
	if (_state == State::kIdle)
	{}
	else if (_state == State::kMoving)
	{
		float speed = 6.0f;
		float expect_radius = 10.0f;
		_heading = (_destination - _pos).getNormalized();
		_pos += _heading * speed;

		if (_pos.distance(_destination) < expect_radius)
			_state = State::kIdle;
	}
}

void Hunter::render()
{
	std::stringstream ss;
	ss << _id;
	GraphicsDriver::instance->drawCircle(_pos, _radius, GraphicsDriver::black);
	GraphicsDriver::instance->drawText(ss.str(), _pos);

	Vec2 sidev = getSide() * _radius / 2;
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos - sidev, GraphicsDriver::black);
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos + _heading * _radius * 2, GraphicsDriver::black);
	GraphicsDriver::instance->drawLine(_pos - sidev, _pos + _heading * _radius * 2, GraphicsDriver::black);
}

