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

	inline int getIntake() const		{ return _intake; }
	inline int getHp() const			{ return _hp; }

	inline int getDamage() const		{ return _damage; }
	inline void setDamage(int damage)	{ _damage = damage; }
	inline int getProjSpeed() const		{ return _proj_speed; }
	inline void setProjSpeed(int range)	{ _proj_speed = range; }

	inline void increase(int intake)	{ _intake += intake; }
	inline void decrease()				{ _intake--; }

	Hunter(World& world, unsigned int id, const Vec2& pos);

	bool upgradeDamage();
	bool upgradeRange();
	void enterMovingState(const Vec2& desti);
	void takeDamage(int damage);

	virtual ~Hunter() {}
	virtual void update();
	virtual void render();
	virtual bool handleMessage(const Message& msg);

private:
	State _state;
	Vec2 _destination;
	int _intake;
	int _hp;
	int _damage;
	int _proj_speed;
};