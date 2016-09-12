#include "Hittable.h"
#include "Interfaces.h"
#include <algorithm>

Hittable::Hittable(IHittable& entity, int max_hp)
	:
	_owner(entity),
	_hp(max_hp),
	_max_hp(max_hp)
{}

void Hittable::HasDamaged(int damage)
{
	if (!_owner.isAlive())
		return;

	_hp = std::max(_hp - damage, 0);

	if (_hp == 0)
	{
		_owner.setDying();
	}
}