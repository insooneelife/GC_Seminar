#pragma once

class Entity;
class TargetSystem
{
public:
	inline unsigned int getTargetID() const { return _targetId; }
	inline void setTargetID(unsigned int value) { _targetId = value; }

	inline bool isAttackable() const { return _attackable; }
	inline void setAttackable(bool value) { _attackable = value; }
	
	inline bool isViewable() const { return _viewable; }
	inline void setViewable(bool value) { _viewable = value; }

	inline float getAttackRange() const { return _attackRange; }
	inline void setAttackRange(float value) { _attackRange = value; }

	inline float getViewRange() const { return _viewRange; }
	inline void setViewRange(float value) { _viewRange = value; }

	TargetSystem(
		Entity& entity,
		float attackRange,
		float viewRange);

	Entity* updateTarget();

private:
	Entity& _entity;
	unsigned int _targetId;
	bool _attackable;
	bool _viewable;
	float _attackRange;
	float _viewRange;
};
