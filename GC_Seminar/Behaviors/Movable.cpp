#include "Movable.h"
#include "../Entity.h"

int Movable::makeDirection(int x, int y, int nu, int de)
{
	// The line gradient of tan(67.5) == 12(numerator) / 5(denominator).
	int a = nu * y - de * x;
	int b = de * y - nu * x;
	int c = de * y + nu * x;
	int d = nu * y + de * x;

	if (a >= 0 && b <= 0)
		return (int)Directions::kRightUp;

	else if (b >= 0 && c >= 0)
		return (int)Directions::kUp;

	else if (c <= 0 && d >= 0)
		return (int)Directions::kLeftUp;

	else if (d <= 0 && a >= 0)
		return (int)Directions::kLeft;

	else if (a <= 0 && b >= 0)
		return (int)Directions::kLeftDown;

	else if (b <= 0 && c <= 0)
		return (int)Directions::kDown;

	else if (c >= 0 && d <= 0)
		return (int)Directions::kRightDown;

	else
		return (int)Directions::kRight;
}

	
Movable::Movable(Entity& entity, float moveSpeed, const Vec2& destination, bool hasDestination)
	:
	_owner(entity),
	_moveSpeed(moveSpeed),
	_destination(destination),
	_hasDestination(hasDestination)
{}

void Movable::updateMovement()
{
	Vec2 heading = (_destination - _owner.getPos()).getNormalized();
	_owner.setHeading(heading);

	Vec2 velocity = heading * _moveSpeed;
	_owner.setPos(_owner.getPos() + velocity);
}
