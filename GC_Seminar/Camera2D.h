#pragma once
#include "Math\Transformations.h"
#include <iostream>

class Camera2D
{
public:
	static void staticInit(float screenX, float screenY);
	static std::unique_ptr<Camera2D> instance;

	inline Vec2 getOrigin() const { return _origin; }
	inline Vec2 getAxisX() const { return _axisX; }
	inline Vec2 getAxisY() const { return _axisY; }
	inline float getScale() const { return _scale; }

	inline void setCamera(const Vec2& origin, const Vec2& axisX, const Vec2& axisY, float scale = 1.0f)
	{
		_origin = origin;
		_axisX = axisX;
		_axisY = axisY;
		_scale = scale;
	}

	inline float getScreenX() const { return _screenX; }
	inline float getScreenY() const { return _screenY; }

	Camera2D(float screenX, float screenY);

	// ���ڷ� ���� ��ġ�� camera�� ���� �������� ��ȯ ��,
	// screen�� �µ��� ��ȯ��Ų ���ο� ��ġ�� ��ȯ�Ѵ�.
	Vec2 carmeraPos(const Vec2& pos);


private:
	float _screenX;
	float _screenY;

	Vec2 _origin;
	Vec2 _axisX;
	Vec2 _axisY;
	float _scale;
};