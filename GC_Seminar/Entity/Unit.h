#pragma once
//------------------------------------------------------------------------
//
//  Name:   Unit.h
//
//  Desc:   
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "GenericEntity.h"

class RenderComponent;
class CollisionComponent;
class MoveComponent;

class Unit : 
	public GenericEntity,
	public ICollisionComponent, 
	public IMoveComponent,
	public IRenderComponent
{
public:

	static Unit* create(World& world, const Vec2& pos);

	Unit(World& world, unsigned int id, const Vec2& pos);
	virtual ~Unit() {}

	virtual Vec2 getPos() const;
	virtual void setPos(const Vec2& pos);
	virtual Vec2 getHeading() const;
	virtual void setHeading(const Vec2& heading);
	virtual b2Transform getTransform() const;
	virtual void setTransform(const b2Transform& trans);

	virtual CollisionComponent& getCollision() const;
	virtual void setCollision(CollisionComponent* const collision);

	virtual MoveComponent& getMove() const;
	virtual void setMove(MoveComponent* const move);

	virtual RenderComponent& getRendering() const;
	virtual void setRendering(RenderComponent* const render);


	virtual void update();
	virtual void render();
	virtual bool handleMessage(const Message& msg);

private:

	RenderComponent* _rendering;
	CollisionComponent* _collision;
	MoveComponent* _move;

};