#include <iostream>
#include <sstream>
#include "Projectile.h"
#include "../GraphicsDriver.h"
#include "../PhysicsManager.h"
#include "../World.h"
#include "../Components/Interfaces.h"
#include "../Components/CollisionComponent.h"
#include "../Components/MoveComponent.h"

namespace
{
	const int kDefaultLifeTime = 50;

	const float kProjectileRenderRadius = 0.15f;
	const float kProjectileBodyRadius = 0.10f;
	const float kProjectileSpeed = 0.1f;
}

Projectile* Projectile::create(
	World& world, const Vec2& pos, const std::string& name, unsigned int owner_id)
{
	unsigned int id = world.genID();
	Projectile* proj = new Projectile(world, id, name, owner_id);

	b2CircleShape circle;
	circle.m_radius = kProjectileBodyRadius;

	CollisionComponent* collision =
		CollisionComponent::create(
			world.getPhysicsMgr()->GetPhysicsWorld(),
			proj,
			&circle,
			b2BodyType::b2_dynamicBody,
			pos,
			true,
			kProjectileBodyRadius,
			proj->getType());

	proj->setCollision(collision);

	MoveComponent* move = new MoveComponent(*proj, kProjectileSpeed, Vec2(0, 0), false);
	proj->setMove(move);

	return proj;
}


Projectile::Projectile(
	World& world,
	unsigned int id,
	const std::string& name,
	unsigned int owner_id)
	:
	GenericEntity(world, id, GenericEntity::Type::kProjectile, name),
	_move(nullptr),
	_collision(nullptr),
	_owner_id(owner_id),
	_life_time(kDefaultLifeTime)
{}

Projectile::~Projectile()
{}

// For ITransformComponent .. 
Vec2 Projectile::getPos() const
{
	return Vec2(_collision->getBody()->GetTransform().p.x, _collision->getBody()->GetTransform().p.y);
}

void Projectile::setPos(const Vec2& pos)
{
	_collision->getBody()->SetTransform(b2Vec2(pos.x, pos.y), _collision->getBody()->GetAngle());
}

Vec2 Projectile::getHeading() const
{
	return Vec2(_collision->getBody()->GetTransform().q.c, _collision->getBody()->GetTransform().q.s);
}

void Projectile::setHeading(const Vec2& heading)
{
	b2Rot rot;
	rot.c = heading.x;
	rot.s = heading.y;
	_collision->getBody()->SetTransform(_collision->getBody()->GetTransform().p, rot.GetAngle());
}

b2Transform Projectile::getTransform() const
{
	return _collision->getBody()->GetTransform();
}

void Projectile::setTransform(const b2Transform& trans)
{
	_collision->getBody()->SetTransform(trans.p, trans.q.GetAngle());
}

// For ICollisionComponent .. 
CollisionComponent& Projectile::getCollision() const
{
	return *_collision;
}

void Projectile::setCollision(CollisionComponent* const collision)
{
	_collision.reset(collision);
}

// For IMoveComponent .. 
MoveComponent& Projectile::getMove() const
{
	return *_move;
}

void Projectile::setMove(MoveComponent* const move)
{
	_move.reset(move);
}


void Projectile::update()
{
	if (_life_time-- < 0)
		_is_garbage = true;

	_move->updateMovement();
	//_collision->getBody()->SetTransform(_body->GetPosition(),)
	//_pos.set(_body->GetPosition().x, _body->GetPosition().y);
}

void Projectile::render()
{
	float radius = _collision->getBRadius();
	Vec2 pos = getPos();
	Vec2 heading = getHeading();
	Vec2 sidev = heading.getPerp() * radius * 0.5f;
	GraphicsDriver::instance->drawLine(pos + sidev, pos - sidev);
	GraphicsDriver::instance->drawLine(pos + sidev, pos + heading * radius * 2);
	GraphicsDriver::instance->drawLine(pos - sidev, pos + heading * radius * 2);
}

