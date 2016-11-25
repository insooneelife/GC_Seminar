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

#include <memory>
#include "GenericEntity.h"
#include "../FSM/StateMachine.h"

class RenderComponent;
class CollisionComponent;
class MoveComponent;
class TargetComponent;
class AttackComponent;
class HitComponent;
class AnimationComponent;

class Unit : 
	public GenericEntity,
	public ICollisionComponent, 
	public IMoveComponent,
	public IAttackComponent,
	public IHitComponent,
	public IAnimationComponent
{
public:
	typedef msm::back::state_machine< Fsm_<Unit> > Fsm;

	static Unit* create(
		World& world, const Vec2& pos, const std::string& name);

	inline Fsm& getFsm() { return _fsm; }

	Unit(World& world, unsigned int id, const Vec2& pos, const std::string& name);
	virtual ~Unit();

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
	
	virtual HitComponent& getHit() const;
	virtual void setHit(HitComponent* const hit);
	virtual void setDead();

	virtual AnimationComponent& getAnimation() const;
	virtual void setAnimation(AnimationComponent* const animation);
	virtual std::string getName() const;

	virtual void update();
	virtual void render();
	virtual bool handleMessage(const Message& msg);

private:

	std::unique_ptr<RenderComponent> _rendering;
	std::unique_ptr<CollisionComponent> _collision;
	std::unique_ptr<MoveComponent> _move;
	std::unique_ptr<TargetComponent> _targetting;
	std::unique_ptr<AttackComponent> _attack;
	std::unique_ptr<HitComponent> _hit;
	std::unique_ptr<AnimationComponent> _animation;
	Fsm _fsm;

	std::string _name;

};