#pragma once
//------------------------------------------------------------------------
//
//  Name:   Projectile.h
//
//  Desc:   
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "GenericEntity.h"

class Projectile 
	:
	public GenericEntity,
	public ICollisionComponent,
	public IMoveComponent

{
public:

	static Projectile* create(
		World& world, const Vec2& pos, const std::string& name, unsigned int owner_id);

	inline unsigned int getOwnerID() const { return _owner_id; }

	Projectile(
		World& world,
		unsigned int id,
		const std::string& name,
		unsigned int owner_id);

	virtual ~Projectile();

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

	
	virtual void update();
	virtual void render();

private:
	std::unique_ptr<CollisionComponent> _collision;
	std::unique_ptr<MoveComponent> _move;
	unsigned int _owner_id;
	int _life_time;
};