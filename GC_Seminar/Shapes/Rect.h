#pragma once
#include "Shape.h"
#include "../Math/Vec2.h"

class Rect : public Shape
{
public:
	inline const Vec2& getTopRight()	const { return _top_right; }
	inline const Vec2& getBottomLeft()	const { return _bottom_left; }
	inline Vec2 getTopLeft()			const { return Vec2(getLeft(), getTop()); }
	inline Vec2 getBottomRight()		const { return Vec2(getRight(), getBottom()); }

	inline const Vec2& getCenter()		const { return _center; }

	inline double getTop()		const { return _top_right.y; }
	inline double getLeft()		const { return _bottom_left.x; }
	inline double getBottom()	const { return _bottom_left.y; }
	inline double getRight()	const { return _top_right.x; }

	Rect(Vec2 bl, Vec2 tr)
		:
		_bottom_left(bl),
		_top_right(tr),
		_center((bl + tr) / 2.0)
	{}

	Rect(Vec2 center, float width, float height)
		:
		_bottom_left(center - (Vec2(width, height) / 2)),
		_top_right(center + (Vec2(width, height) / 2)),
		_center(center)
	{}

	virtual bool collide(const Shape* const other) const;
	virtual bool collide(const Rect* const other) const;
	virtual bool collide(const Circle* const other) const;

	virtual void render();

private:
	Vec2		_bottom_left;
	Vec2		_top_right;
	Vec2		_center;
};
