//------------------------------------------------------------------------
//
//  Name:		Interfaces.h
//
//  Desc:		Interfaces for composition in behaviors and game objects.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#pragma once

#include <string>
#include "../Math/Vec2.h"

class Message;
class IMessageHandler
{
public:
	virtual bool handleMessage(const Message& msg) = 0;
};

class Renderable;
class IRenderable
{
public:
	virtual Renderable& getRenderable() const = 0;
	virtual Vec2 getPos() const = 0;
};

class Animation;
class IAnimation : public IRenderable
{
public:
	virtual Animation& getAnimation() const = 0;
	virtual std::string getName() const = 0;
};

class Movable;
class IMovable
{
public:
	virtual Movable& getMove() const = 0;
	virtual Vec2 getPos() const = 0;
	virtual void setPos(const Vec2& pos) = 0;
	virtual Vec2 getHeading() const = 0;
	virtual void setHeading(const Vec2& heading) = 0;
};

class Hittable;
class IHittable : public IMessageHandler, public IAnimation
{
public:
	virtual Hittable& getHittable() const = 0;
	virtual bool isAlive() const = 0;
	virtual void setDying() = 0;
};


class TargetSystem;
class ITargetable
{
	virtual TargetSystem& getTargetSys() const = 0;
};

/*
class IAttackable : ITargetable, IMessageHandler
{
	AttackSystem AttackSys{ get; set; }
}

class IMovable
{
	Movable Move{ get; set; }
	Point2D Pos{ get; }
}

class ITrainable
{
	TrainSystem TrainSys{ get; set; }
}


class IClickable
{
	Clickable Click{ get; set; }
	Point2D Pos{ get; }

	bool Collide(Point2D clickedPos);
	void EventOnSelected(uint playerId);
	void EventOnDeselected();
	void EventOnTrySelected(bool onOff);
}

*/