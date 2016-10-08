//------------------------------------------------------------------------
//
//  Name:   Shape.h
//
//  Desc:   Base class for varius shapes that are used for collision checking.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#pragma once


#include "../Engine.h"
#include "../Math/Vec2.h"

class Rect;
class Circle;
class Shape
{
public:
	static bool collide(const Rect* const r, const Circle* const c);
	static bool collide(const Circle* const c, const Rect* const r);
	static bool collide(const Rect* const r1, const Rect* const r2);
	static bool collide(const Circle* const c1, const Circle* const c2);

	virtual bool collide(const Shape* const other) const = 0;
	virtual bool collide(const Rect* const other) const = 0;
	virtual bool collide(const Circle* const other) const = 0;

	virtual void render() = 0;
};



