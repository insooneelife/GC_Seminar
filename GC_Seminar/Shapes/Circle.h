#pragma once
#include "Shape.h"

// 원을 나타내는 shape
class Circle : public Shape
{
public:
	inline Vec2 getCenter() const { return _center; }

	inline float getRadius() const { return _radius; }

	Circle::Circle()
		: _center(0, 0), _radius(1)
	{}

	Circle::Circle(float x, float y, float r)
		: _center(x, y), _radius(r)
	{}

	Circle::Circle(const Vec2& origin, float r)
		: _center(origin), _radius(r)
	{}

	virtual bool collide(const Shape* const other) const;
	virtual bool collide(const Rect* const other) const;
	virtual bool collide(const Circle* const other) const;

	// 원을 그리는 함수
	virtual void render();

private:
	Vec2 _center;
	float _radius;
};