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
#include "../FSM/StateMachine.h"

class RenderComponent;
class CollisionComponent;
class MoveComponent;
class TargetComponent;
class AttackComponent;

class Unit : 
	public GenericEntity,
	public ICollisionComponent, 
	public IMoveComponent,
	public IRenderComponent,
	public IAttackComponent
{
public:
	typedef msm::back::state_machine< Fsm_<Unit> > Fsm;

	static Unit* create(World& world, const Vec2& pos);

	inline Fsm& getFsm() { return _fsm; }

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

	virtual TargetComponent& getTargetting() const;
	virtual void setTargetting(TargetComponent* const target);
	virtual bool isAlive() const;
	virtual unsigned int getID() const override;

	virtual AttackComponent& getAttack() const;
	virtual void setAttack(AttackComponent* const attack);
	
	virtual void update();
	virtual void render();
	virtual bool handleMessage(const Message& msg);

private:

	RenderComponent* _rendering;
	CollisionComponent* _collision;
	MoveComponent* _move;
	TargetComponent* _target;
	AttackComponent* _attack;
	Fsm _fsm;

};