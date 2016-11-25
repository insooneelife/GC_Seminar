#pragma once

#include <functional>

class World;
class ITargetComponent;
class TargetComponent
{
public:
	static ITargetComponent* getClosestTarget(
		World& world,
		ITargetComponent& entity,
		float range,
		std::function<bool(unsigned int, unsigned int, bool)> filter);

	ITargetComponent* getTarget()					{ return _target; }

	inline bool isAttackable() const				{ return _attackable; }
	inline void setAttackable(bool value)			{ _attackable = value; }
	
	inline bool isViewable() const					{ return _viewable; }
	inline void setViewable(bool value)				{ _viewable = value; }

	inline float getAttackRange() const				{ return _attackRange; }
	inline void setAttackRange(float value)			{ _attackRange = value; }

	inline float getViewRange() const				{ return _viewRange; }
	inline void setViewRange(float value)			{ _viewRange = value; }

	TargetComponent(
		ITargetComponent& entity,
		float attackRange,
		float viewRange);

	void updateTarget(World& world);

private:
	ITargetComponent& _entity;
	ITargetComponent* _target;
	bool _attackable;
	bool _viewable;
	float _attackRange;
	float _viewRange;
};
