#pragma once

//------------------------------------------------------------------------
//
//  Name:   Geometry.h
//
//  Desc:   Functions for 2D geometry collisions
//
//  Author: Insub Im (insooneelife@naver.com)
//------------------------------------------------------------------------

#include "Shape.h"
#include "Rect.h"
#include "Circle.h"
namespace
{
	bool collide(const Rect* const r, const Circle* const c);

	bool collide(const Circle* const c, const Rect* const r);

	bool collide(const Rect* const r1, const Rect* const r2);

	bool collide(const Circle* const c1, const Circle* const c2);
}
