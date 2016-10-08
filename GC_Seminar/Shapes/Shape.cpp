#include "Shape.h"
#include "Rect.h"
#include "Circle.h"


bool Shape::collide(const Rect* const r, const Circle* const c)
{
	Vec2 bl(r->getBottomLeft());
	Vec2 br(r->getBottomRight());
	Vec2 tl(r->getTopLeft());
	Vec2 tr(r->getTopRight());

	return c->getCenter().distance(bl) <= c->getRadius() ||
		c->getCenter().distance(br) <= c->getRadius() ||
		c->getCenter().distance(tl) <= c->getRadius() ||
		c->getCenter().distance(tr) <= c->getRadius();
}

bool Shape::collide(const Circle* const c, const Rect* const r)
{
	return collide(r, c);
}

bool Shape::collide(const Rect* const r1, const Rect* const r2)
{
	return !((r1->getTop() <= r2->getBottom()) ||
		(r1->getBottom() >= r2->getTop()) ||
		(r1->getLeft() >= r2->getRight()) ||
		(r1->getRight() <= r2->getLeft()));
}

bool Shape::collide(const Circle* const c1, const Circle* const c2)
{
	return (c1->getCenter() - c2->getCenter()).length() <= c1->getRadius() + c2->getRadius();
}
