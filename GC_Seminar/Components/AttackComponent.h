#pragma once

class IAttackComponent;
class AttackComponent
{
public:
	inline int getDamage() const				{ return _damage; }
	inline void setDamage(int value)			{ _damage = value; }

	inline int getAttackFrame() const			{ return _attackFrame; }
	inline void setAttackFrame(int value)		{ _attackFrame = value; }

	inline int getAttackFrameDelay() const		{ return _attackFrameDelay; }
	inline void setAttackFrameDelay(int value)	{ _attackFrameDelay = value; }

	AttackComponent(IAttackComponent& entity, int damage, int attackFrameDelay)
		:
		_owner(entity),
		_damage(damage),
		_attackFrame(0),
		_attackFrameDelay(attackFrameDelay)
	{}

	virtual void updateAttack() = 0;

protected:

	IAttackComponent& _owner;
	int _damage;
	int _attackFrame;
	int _attackFrameDelay;
};


class MeleeAttack : public AttackComponent
{
public:
	MeleeAttack(IAttackComponent& entity, int damage, int attackFrameDelay)
		:
		AttackComponent(entity, damage, attackFrameDelay)
	{}

	virtual void updateAttack() override;
};


class RangeAttack : public AttackComponent
{
public:
	RangeAttack(IAttackComponent& entity, int damage, int attackFrameDelay)
		:
		AttackComponent(entity, damage, attackFrameDelay)
	{}

	virtual void updateAttack() override;
};