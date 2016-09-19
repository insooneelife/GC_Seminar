#include "TargetSystem.h"
#include "../World.h"
#include "../Entity.h"
#include "../EntityManager.h"
#include "../GraphicsDriver.h"

TargetSystem::TargetSystem(
	Entity& entity,
	float attackRange,
	float viewRange)
	:
	_owner(entity),
	_targetEnt(nullptr),
	_targetId(0),
	_attackable(false),
	_viewable(false),
	_attackRange(attackRange),
	_viewRange(viewRange)
{}

Entity* TargetSystem::updateTarget()
{
	_targetEnt = EntityManager::instance->getEntity(_targetId);

	// If target presents..
	if (_targetEnt != nullptr && _targetEnt->isAlive())
	{
		_attackable = (_owner.getPos() - _targetEnt->getPos()).length() <= _attackRange;
		_viewable = (_owner.getPos() - _targetEnt->getPos()).length() <= _viewRange;

		if (_viewable)
			return _targetEnt;
		else
			return _targetEnt = nullptr;
	}

	// Otherwise, we have to set a new target.
	else
	{
		float distance = -1;
		_targetEnt = _owner.getWorld()
			.getClosestEntityFromPos(_owner, distance);

		if (_targetEnt == nullptr)
		{
			_attackable = false;
			_viewable = false;
			_targetId = 0;
			return nullptr;
		}
		else if (distance < sqrt(_viewRange * _viewRange))
		{
			_targetId = _targetEnt->getID();
			_attackable = true;
			_viewable = true;
			return _targetEnt;
		}
		else
		{
			_targetEnt = nullptr;
			_attackable = false;
			_viewable = false;
			_targetId = 0;
			return nullptr;
		}
	}
}

void TargetSystem::render()
{
	if(_viewable)
		GraphicsDriver::instance->drawLine(_owner.getPos(), _targetEnt->getPos(), GraphicsDriver::red);
}