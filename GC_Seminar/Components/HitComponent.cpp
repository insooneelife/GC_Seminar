#include "HitComponent.h"
#include "Interfaces.h"
#include "../Entity/GenericEntity.h"
#include "../GraphicsDriver.h"
#include <algorithm>

HitComponent::HitComponent(IHitComponent& entity, int max_hp)
	:
	_owner(entity),
	_hp(max_hp),
	_max_hp(max_hp)
{}

void HitComponent::takeDamaged(int damage)
{
	if (!_owner.isAlive())
		return;

	_hp = std::max(_hp - damage, 0);

	if (_hp == 0)
		_owner.setDead();
}

