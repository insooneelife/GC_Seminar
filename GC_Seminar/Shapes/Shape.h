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

// 여러가지의 shape들에 일관적인 충돌판별을 적용하기 위해 Shape class를 만들고 상속받도록 설계한다.
class Shape
{
public:
	// 실제 shape들의 충돌을 판별하는 함수
	static bool collide(const Rect* const r, const Circle* const c);
	static bool collide(const Circle* const c, const Rect* const r);
	static bool collide(const Rect* const r1, const Rect* const r2);
	static bool collide(const Circle* const c1, const Circle* const c2);

	// Double dispatching 기법
	virtual bool collide(const Shape* const other) const = 0;
	virtual bool collide(const Rect* const other) const = 0;
	virtual bool collide(const Circle* const other) const = 0;

	virtual void render() = 0;
};



