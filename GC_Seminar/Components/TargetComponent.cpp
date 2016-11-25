#include "TargetComponent.h"
#include "Interfaces.h"
#include "../World.h"
#include "../Entity/GenericEntity.h"
#include "../Entity/Unit.h"
#include "../EntityManager.h"
#include "../PhysicsManager.h"
#include "CollisionComponent.h"


TargetComponent::TargetComponent(
	ITargetComponent& entity,
	float attackRange,
	float viewRange)
	:
	_entity(entity),
	_target(nullptr),
	_attackable(false),
	_viewable(false),
	_attackRange(attackRange),
	_viewRange(viewRange)
{}

void TargetComponent::updateTarget(World& world)
{
	// If target presents..
	if (_target != nullptr && _target->isAlive())
	{
		_attackable = (_entity.getPos() - _target->getPos()).length() <= _attackRange;
		_viewable = (_entity.getPos() - _target->getPos()).length() <= _viewRange;

		return;
	}
	// Otherwise, we have to set a new target.
	else
	{
		_target = getClosestTarget(
			world, _entity, _viewRange,
			[](unsigned int id1, unsigned int id2, bool dead) 
		{ 
			return id1 == id2 || dead; 
		});
		
		if (_target == nullptr)
		{
			_attackable = false;
			_viewable = false;
			return;
		}

		float distance = _target->getPos().distance(_entity.getPos());

		if (distance < sqrt(_viewRange * _viewRange))
		{
			_attackable = (_entity.getPos() - _target->getPos()).length() <= _attackRange;
			_viewable = (_entity.getPos() - _target->getPos()).length() <= _viewRange;
			return;
		}
		else
		{
			_attackable = false;
			_viewable = false;
			return;
		}
	}
}

ITargetComponent* TargetComponent::getClosestTarget(
	World& world,
	ITargetComponent& entity,
	float range,
	std::function<bool(unsigned int, unsigned int, bool)> filter)
{
	EntityAABBCallback callback;
	world.getPhysicsMgr()->QueryAABB(
		entity.getPos(), range, range, &callback);

	float min_dist = std::numeric_limits<float>::max();
	ITargetComponent* closest_target = nullptr;

	for (auto e : callback.foundEntities)
	{
		ITargetComponent* target = nullptr;
		if (e->getCollision().getOwnerType() == GenericEntity::kStructure)
		{
			//target = static_cast<Structure*>(e);
		}
		else if (e->getCollision().getOwnerType() == GenericEntity::kUnit)
		{
			target = static_cast<Unit*>(e);
		}

		if (target == nullptr)
			continue;

		if (filter(entity.getID(), target->getID(), !target->isAlive()))
			continue;

		float dist = target->getPos().distance(entity.getPos());
		if (min_dist > dist)
		{
			min_dist = dist;
			closest_target = target;
		}
	}
	return closest_target;
}
