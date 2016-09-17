#pragma once

class Entity;
class AttackSystem
{
public:
	inline int getDamage() const				{ return _damage; }
	inline void setDamage(int value)			{ _damage = value; }

	inline int getAttackFrame() const			{ return _attackFrame; }
	inline void setAttackFrame(int value)		{ _attackFrame = value; }

	inline int getAttackFrameDelay() const		{ return _attackFrameDelay; }
	inline void setAttackFrameDelay(int value)	{ _attackFrameDelay = value; }

	AttackSystem(Entity& entity, int damage, int attackFrameDelay)
		:
		_owner(entity),
		_damage(damage),
		_attackFrame(0),
		_attackFrameDelay(attackFrameDelay)
	{}

	virtual void updateAttack() = 0;

protected:

	Entity& _owner;
	int _damage;
	int _attackFrame;
	int _attackFrameDelay;
};


class MeleeAttack : public AttackSystem
{
public:
	MeleeAttack(Entity& entity, int damage, int attackFrameDelay)
		:
		AttackSystem(entity, damage, attackFrameDelay)
	{}

	virtual void updateAttack() override;
};


class RangeAttack : public AttackSystem
{
public:
	RangeAttack(Entity& entity, int damage, int attackFrameDelay)
		:
		AttackSystem(entity, damage, attackFrameDelay)
	{}

	virtual void updateAttack() override;
};