#include "AttackComponent.h"
#include "TargetComponent.h"
#include "Interfaces.h"
#include "../Entity/GenericEntity.h"
#include "../EntityManager.h"
#include "../World.h"


void MeleeAttack::updateAttack(World& world)
{
	EntityManager::instance->dispatchMsg(
		_owner.getID(),
		_owner.getTargetting().getTarget()->getID(),
		Message::MsgType::kDamage,
		&_damage);
}


void RangeAttack::updateAttack(World& world)
{
	world.createProjectile("Fire", _owner.getPos(), _owner.getID());
}
