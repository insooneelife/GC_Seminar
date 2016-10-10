#pragma once
#include "Math\Transformations.h"
#include <iostream>

// Transform�� �̿��Ͽ� 2D camera�� ����� ����.
// Camera�� ��� �� ���ؿ��� ���踦 �ٶ� ���� ����� ȭ�鿡 ����� �ش�.
// ȭ�鿡 ����ϴ� �κ��� GraphicsDriver�� ����ϰ� �����Ƿ�,
// camera������ ��ǥ��ȯ�� ������ָ� �ȴ�.

// Camera ���� ��ǥ��ȯ��
// camera �������� ������ȯ�� �� ��,
// camera zoom�� �°� ũ�⺯ȯ�� �Ѵ�.


class Camera2D
{
public:
	static void staticInit(float screenX, float screenY);
	static std::unique_ptr<Camera2D> instance;

	inline Vec2 getOrigin() const { return _origin; }
	inline Vec2 getAxisX() const { return _axisX; }
	inline Vec2 getAxisY() const { return _axisY; }
	inline Vec2 getScale() const { return _scale; }
	inline void setScale(const Vec2& scale) { _scale = scale; }

	inline void setCamera(
		const Vec2& origin,
		const Vec2& axisX,
		const Vec2& axisY,
		Vec2 scale = Vec2(1.0f, 1.0f))
	{
		_origin = origin;
		_axisX = axisX;
		_axisY = axisY;
		_scale = scale;
	}

	inline float getScreenX() const { return _screenX; }
	inline float getScreenY() const { return _screenY; }

	Camera2D(float screenX, float screenY);

	Vec2 carmeraPos(const Vec2& pos);


private:
	float _screenX;
	float _screenY;

	Vec2 _origin;
	Vec2 _axisX;
	Vec2 _axisY;
	Vec2 _scale;
};