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

	Projectile(
		World& world,
		unsigned int id,
		unsigned int owner_id,
		const Vec2& pos,
		const Vec2& heading,
		int proj_speed);

	virtual ~Projectile() {}
	virtual void update();
	virtual void render();

private:

	unsigned int _owner_id;
	int _life_time;
	int _proj_speed;
};