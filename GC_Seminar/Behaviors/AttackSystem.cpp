#include "AttackSystem.h"
#include "../Entity.h"
#include "../EntityManager.h"


void MeleeAttack::updateAttack()
{
	EntityManager::instance->dispatchMsg(
		_owner.getID(),
		_owner.getTargetSys().getTargetID(),
		Message::MsgType::Damage,
		&_damage);
}


void RangeAttack::updateAttack()
{
	//_owner.Engine.World.CreateProjectile("Ball", _owner.PlayerId, _owner.LocalPos(), _targetSys.TargetId, 30);
}
