#include "Camera2D.h"

#include <iostream>

std::unique_ptr<Camera2D> Camera2D::instance = nullptr;

void Camera2D::staticInit(float screenX, float screenY)
{
	instance.reset(new Camera2D(screenX, screenY));
}

Camera2D::Camera2D(float screenX, float screenY)
	:
	_screenX(screenX),
	_screenY(screenY),
	_origin(0, 0),
	_axisX(1, 0),
	_axisY(0, 1),
	_scale(1.0f)
{}

Vec2 Camera2D::carmeraPos(const Vec2& pos)
{
	Vec2 convertPos = pointToLocalSpace(pos, _axisX, _axisY, _origin);
	
	convertPos = Vec2(convertPos.x, _screenY - convertPos.y);
	return convertPos;
}
