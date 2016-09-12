//------------------------------------------------------------------------
//
//  Name:		Hittable.h
//
//  Desc:		Defines behaviors of hittable object.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------
#pragma once

class IHittable;
class Hittable
{
public:

	inline int	getHp()	const			{ return _hp; }
	inline void setHp(int hp)			{ _hp = hp; }

	inline int	getMaxHp() const		{ return _max_hp; }
	inline void setMaxHp(int max_hp)	{ _max_hp = max_hp; }

	Hittable(IHittable& entity, int max_hp);

	virtual void HasDamaged(int damage);

private:

	IHittable& _owner;
	int _hp;
	int _max_hp;
};