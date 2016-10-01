#pragma once
//------------------------------------------------------------------------
//
//  Name:   Projectile.h
//
//  Desc:   The entitiy which hunter shoots to other.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "Entity.h"

class Projectile : public Entity
{
public:
	inline unsigned int getOwnerID() const { return _owner_id; }

	virtual ~Projectile() {}
	virtual void update();
	virtual void render();

	Projectile(World& world, unsigned int id, unsigned int owner_id, const Vec2& pos)
		:
		Entity(world, id, pos, 15.0f, Entity::Type::kProjectile),
		_owner_id(owner_id)
	{}

private:
	unsigned int _owner_id;
};