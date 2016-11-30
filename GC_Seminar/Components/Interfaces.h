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
#include <Box2D/Box2D.h>

class Message;
class IMessageHandler
{
public:
	virtual bool handleMessage(const Message& msg) = 0;
	virtual unsigned int getID() const = 0;
};

class TransformComponent;
class ITransformComponent
{
public:
	virtual Vec2 getPos() const = 0;
	virtual void setPos(const Vec2& pos) = 0;
	virtual Vec2 getHeading() const = 0;
	virtual void setHeading(const Vec2& heading) = 0;
	virtual b2Transform getTransform() const = 0;
	virtual void setTransform(const b2Transform& trans) = 0;
};

class GenericEntity;
class CollisionComponent;
class ICollisionComponent : public ITransformComponent
{
public:
	virtual CollisionComponent& getCollision() const = 0;
	virtual void setCollision(CollisionComponent* const collision) = 0;
};

class RenderComponent;
class IRenderComponent : public ITransformComponent
{
public:
	virtual RenderComponent& getRendering() const = 0;
	virtual void setRendering(RenderComponent* const render) = 0;
};

class MoveComponent;
class IMoveComponent : public ITransformComponent
{
public:
	virtual MoveComponent& getMove() const = 0;
	virtual void setMove(MoveComponent* const move) = 0;
};


class AnimationComponent;
class IAnimationComponent : public IRenderComponent
{
public:
	virtual AnimationComponent& getAnimation() const = 0;
	virtual void setAnimation(AnimationComponent* const animation) = 0;
	virtual std::string getName() const = 0;
};


class TargetComponent;
class ITargetComponent : public ITransformComponent
{
public:
	virtual TargetComponent& getTargetting() const = 0;
	virtual void setTargetting(TargetComponent* const target) = 0;
	virtual bool isAlive() const = 0;
	virtual unsigned int getID() const = 0;
};

class AttackComponent;
class IAttackComponent : public ITargetComponent, public IMessageHandler
{
public:
	virtual AttackComponent& getAttack() const = 0;
	virtual void setAttack(AttackComponent* const attack) = 0;
	virtual unsigned int getID() const = 0;
};

class HitComponent;
class IHitComponent
{
public:
	virtual HitComponent& getHit() const = 0;
	virtual void setHit(HitComponent* const hit) = 0;
	virtual bool isAlive() const = 0;
	virtual void setDead() = 0;
};

class ClickComponent;
class IClickComponent : public ICollisionComponent
{
	virtual ClickComponent& getClick() const = 0;
	virtual void setClick(ClickComponent* const click) = 0;

	virtual bool isCollide(Vec2 clicked_pos) const = 0;
	virtual void eventOnSelected(unsigned int pid) = 0;
	virtual void eventOnDeselected() = 0;
	virtual void eventOnTrySelect(bool touched) = 0;
};