#include "Hittable.h"
#include "Interfaces.h"
#include "../Entity.h"
#include "../StateMachine/StateMachine.h"
#include "../GraphicsDriver.h"
#include <algorithm>

Hittable::Hittable(Entity& entity, int max_hp)
	:
	_owner(entity),
	_hp(max_hp),
	_max_hp(max_hp)
{}

void Hittable::takeDamaged(int damage)
{
	if (!_owner.isAlive())
		return;

	_hp = std::max(_hp - damage, 0);

	if (_hp == 0)
		_owner.getFsm().process_event(Entity::Fsm::hasToDie<Entity>(_owner));
}