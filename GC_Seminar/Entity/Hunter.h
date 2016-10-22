#pragma once
//------------------------------------------------------------------------
//
//  Name:   Hunter.h
//
//  Desc:   The entity which intakes other entities and grows bigger.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "Entity.h"

class Hunter : public Entity
{
public:
	enum State
	{
		kIdle,
		kMoving
	};

	inline int getExp() const			{ return _experience; }
	inline void setExp(int exp)			{ _experience = exp; }
	inline int getHp() const			{ return _hp; }

	inline int getDamage() const		{ return _damage; }
	inline void setDamage(int damage)	{ _damage = damage; }
	inline int getProjSpeed() const		{ return _proj_speed; }
	inline void setProjSpeed(int range)	{ _proj_speed = range; }

	inline bool isPlayer() const		{ return _is_player; }

	Hunter(World& world, unsigned int id, const Vec2& pos);
	virtual ~Hunter();

	bool upgradeDamage();
	bool upgradeRange();
	void enterMovingState(const Vec2& desti);
	void takeDamage(int damage, unsigned int who);

	virtual void update();
	virtual void render();
	virtual bool handleMessage(const Message& msg);

private:
	State _state;
	Vec2 _destination;
	int _experience;
	int _hp;
	int _damage;
	int _proj_speed;
	bool _is_player;
};