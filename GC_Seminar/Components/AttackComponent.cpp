#include "AttackComponent.h"
#include "TargetComponent.h"
#include "Interfaces.h"
#include "../Entity/GenericEntity.h"
#include "../EntityManager.h"


void MeleeAttack::updateAttack()
{
	EntityManager::instance->dispatchMsg(
		_owner.getID(),
		_owner.getTargetting().getTarget()->getID(),
		Message::MsgType::kDamage,
		&_damage);
}


void RangeAttack::updateAttack()
{
	//_owner.Engine.World.CreateProjectile("Ball", _owner.PlayerId, _owner.LocalPos(), _targetSys.TargetId, 30);
}
