//------------------------------------------------------------------------
//
//  Name:		Movable.h
//
//  Desc:		Defines behaviors of movable object.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#pragma once

#include "../Math/Vec2.h"

class IMovable;
class Movable
{
public:
	// 8 Directions
	enum Directions
	{
		kDown, kLeftDown, kLeft, kLeftUp, kUp, kRightUp, kRight, kRightDown
	};

	static int makeDirection(int x, int y, int nu = 12, int de = 5);

	inline float getMoveSpeed() const			{ return _moveSpeed; }
	inline void setMoveSpeed(float value)		{ _moveSpeed = value; }

	inline Vec2 getDestination() const			{ return _destination; }
	inline void setDestination(Vec2 value)		{ _destination = value; }

	inline bool getHasDestination() const		{ return _hasDestination; }
	inline void getHasDestination(bool value)	{ _hasDestination = value; }

	Movable(IMovable& entity, float moveSpeed, const Vec2& destination, bool hasDestination);

	void updateMovement();

private:
	IMovable& _owner;
	float _moveSpeed;
	Vec2 _destination;
	bool _hasDestination;
};