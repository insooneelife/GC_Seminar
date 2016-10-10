#pragma once
#include "Math\Transformations.h"
#include <iostream>

// Transform을 이용하여 2D camera를 만들어 보자.
// Camera는 어느 한 기준에서 세계를 바라볼 때의 장면을 화면에 출력해 준다.
// 화면에 출력하는 부분은 GraphicsDriver가 담당하고 있으므로,
// camera에서는 좌표변환을 담당해주면 된다.

// Camera 통한 좌표변환은
// camera 기준으로 지역변환을 한 후,
// camera zoom에 맞게 크기변환을 한다.


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