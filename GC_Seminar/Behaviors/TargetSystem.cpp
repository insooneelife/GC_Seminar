#include "TargetSystem.h"
#include "../World.h"
#include "../Entity.h"
#include "../EntityManager.h"


TargetSystem::TargetSystem(
	Entity& entity,
	float attackRange,
	float viewRange)
	:
	_entity(entity),
	_targetId(0),
	_attackable(false),
	_viewable(false),
	_attackRange(attackRange),
	_viewRange(viewRange)
{}

Entity* TargetSystem::updateTarget()
{
	Entity* targetEnt = EntityManager::instance->getEntity(_targetId);

	// If target presents..
	if (targetEnt != nullptr && targetEnt->isAlive())
	{
		_attackable = (_entity.getPos() - targetEnt->getPos()).length() <= _attackRange;
		_viewable = (_entity.getPos() - targetEnt->getPos()).length() <= _viewRange;

		return targetEnt;
	}
	// Otherwise, we have to set a new target.
	else
	{
		float distance = -1;
		targetEnt = _entity.getWorld()
			.getClosestEntityFromPos(_entity, distance);

		if (targetEnt == nullptr)
		{
			_attackable = false;
			_viewable = false;
			_targetId = 0;
			return nullptr;
		}

		if (distance < sqrt(_viewRange * _viewRange))
		{
			_targetId = targetEnt->getID();
			_attackable = (_entity.getPos() - targetEnt->getPos()).length() <= _attackRange;
			_viewable = (_entity.getPos() - targetEnt->getPos()).length() <= _viewRange;
			return targetEnt;
		}
		else
		{
			_attackable = false;
			_viewable = false;
			_targetId = 0;
			return nullptr;
		}
	}
}