#include "PhysicsManager.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <iostream>
#include "World.h"
#include "Entity/Entity.h"
#include "Entity/Hunter.h"
#include "Entity/Prey.h"
#include "Entity/Projectile.h"
#include "Entity/Wall.h"


bool PhysicsManager::CheckContact(
	const b2Shape* shapeA, int32 indexA,
	const b2Shape* shapeB, int32 indexB,
	const b2Transform& xfA, const b2Transform& xfB,
	b2DistanceOutput& output)
{
	b2DistanceInput input;
	input.proxyA.Set(shapeA, indexA);
	input.proxyB.Set(shapeB, indexB);
	input.transformA = xfA;
	input.transformB = xfB;
	input.useRadii = true;

	b2SimplexCache cache;
	cache.count = 0;

	b2Distance(&output, &cache, &input);

	return output.distance < 10.0f * b2_epsilon;
}


PhysicsManager::PhysicsManager(float worldX, float worldY)
	:
	m_pointCount(0)
{
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	_world = new b2World(gravity);
	_destruction_listener.physics = this;
	_world->SetDestructionListener(&_destruction_listener);
	_world->SetContactListener(this);
	_world->SetDebugDraw(GraphicsDriver::instance.get());

	// Ground body
	{
		b2BodyDef bd;
		_ground = _world->CreateBody(&bd);

		b2Vec2 points[] =
		{
			b2Vec2(-worldX, -worldY),
			b2Vec2(worldX, -worldY),
			b2Vec2(worldX, worldY),
			b2Vec2(-worldX, worldY)
		};

		for (int i = 0; i < 4; i++)
		{
			int j = (i + 1) % 4;
			b2EdgeShape shape;
			shape.Set(points[i], points[j]);
			_ground->CreateFixture(&shape, 0.0f);
		}
	}
}

void PhysicsManager::Step()
{
	uint32 flags = 0;
	flags += _settings.drawShapes		* b2Draw::e_shapeBit;
	flags += _settings.drawJoints		* b2Draw::e_jointBit;
	flags += _settings.drawAABBs		* b2Draw::e_aabbBit;
	flags += _settings.drawCOMs			* b2Draw::e_centerOfMassBit;
	GraphicsDriver::instance->SetFlags(flags);

	float32 timeStep = _settings.hz > 0.0f ? 1.0f / _settings.hz : float32(0.0f);

	_world->Step(
		timeStep,
		_settings.velocityIterations,
		_settings.positionIterations);
}

void PhysicsManager::Render()
{
	_world->DrawDebugData();

	if (_settings.drawContactPoints)
	{
		const float32 k_impulseScale = 0.1f;
		const float32 k_axisScale = 0.3f;

		for (int32 i = 0; i < m_pointCount; ++i)
		{
			ContactPoint* point = m_points + i;

			if (point->state == b2_addState)
			{
				// Add
				GraphicsDriver::instance->DrawPoint(point->position, 10.0f, b2Color(0.3f, 0.95f, 0.3f));
			}
			else if (point->state == b2_persistState)
			{
				// Persist
				GraphicsDriver::instance->DrawPoint(point->position, 5.0f, b2Color(0.3f, 0.3f, 0.95f));
			}

			if (_settings.drawContactNormals)
			{
				b2Vec2 p1 = point->position;
				b2Vec2 p2 = p1 + k_axisScale * point->normal;
				GraphicsDriver::instance->DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.9f));
			}
			else if (_settings.drawContactImpulse)
			{
				b2Vec2 p1 = point->position;
				b2Vec2 p2 = p1 + k_impulseScale * point->normalImpulse * point->normal;
				GraphicsDriver::instance->DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.3f));
			}

			if (_settings.drawFrictionImpulse)
			{
				b2Vec2 tangent = b2Cross(point->normal, 1.0f);
				b2Vec2 p1 = point->position;
				b2Vec2 p2 = p1 + k_impulseScale * point->tangentImpulse * tangent;
				GraphicsDriver::instance->DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.3f));
			}
		}
	}
}


void PhysicsManager::BeginContact(b2Contact* contact)
{
	//check if both fixtures were balls
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserDataA && bodyUserDataB)
	{
		Entity* entA = static_cast<Entity*>(bodyUserDataA);
		Entity* entB = static_cast<Entity*>(bodyUserDataB);

		if (entA->getType() == Entity::Type::kHunter && entB->getType() == Entity::Type::kHunter)
			World::collide(*static_cast<Hunter*>(entA), *static_cast<Hunter*>(entB));

		else if (entA->getType() == Entity::Type::kHunter && entB->getType() == Entity::Type::kProjectile)
			World::collide(*static_cast<Hunter*>(entA), *static_cast<Projectile*>(entB));

		else if (entA->getType() == Entity::Type::kProjectile && entB->getType() == Entity::Type::kHunter)
			World::collide(*static_cast<Hunter*>(entB), *static_cast<Projectile*>(entA));

		else if (entA->getType() == Entity::Type::kProjectile && entB->getType() == Entity::Type::kPrey)
			World::collide(*static_cast<Projectile*>(entA), *static_cast<Prey*>(entB));

		else if (entA->getType() == Entity::Type::kPrey && entB->getType() == Entity::Type::kProjectile)
			World::collide(*static_cast<Projectile*>(entB), *static_cast<Prey*>(entA));

		else if (entA->getType() == Entity::Type::kHunter && entB->getType() == Entity::Type::kWall)
			World::collide(*static_cast<Hunter*>(entA), *static_cast<Wall*>(entB));

		else if (entA->getType() == Entity::Type::kWall && entB->getType() == Entity::Type::kHunter)
			World::collide(*static_cast<Hunter*>(entB), *static_cast<Wall*>(entA));
	}
}

void PhysicsManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	const b2Manifold* manifold = contact->GetManifold();

	if (manifold->pointCount == 0)
	{
		return;
	}

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
	b2GetPointStates(state1, state2, oldManifold, manifold);

	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	for (int32 i = 0; i < manifold->pointCount && m_pointCount < 2048; ++i)
	{
		ContactPoint* cp = m_points + m_pointCount;
		cp->fixtureA = fixtureA;
		cp->fixtureB = fixtureB;
		cp->position = worldManifold.points[i];
		cp->normal = worldManifold.normal;
		cp->state = state2[i];
		cp->normalImpulse = manifold->points[i].normalImpulse;
		cp->tangentImpulse = manifold->points[i].tangentImpulse;
		cp->separation = worldManifold.separations[i];
		++m_pointCount;
	}
}


b2Body* PhysicsManager::CreateApplyForceBody(float x, float y, b2Shape* shape)
{
	// Create body
	b2BodyDef bd;
	bd.position.Set(x, y);
	bd.type = b2BodyType::b2_dynamicBody;
	bd.allowSleep = false;

	b2Body* body = _world->CreateBody(&bd);

	b2FixtureDef fd;
	fd.shape = shape;
	fd.density = 1.0f;
	fd.friction = 0.0f;
	fd.restitution = 0.0f;
	body->CreateFixture(&fd);

	// Apply force
	float32 gravity = 10.0f;
	float32 I = body->GetInertia();
	float32 mass = body->GetMass();

	// For a circle: I = 0.5 * m * r * r ==> r = sqrt(2 * I / m)
	float32 radius = b2Sqrt(2.0f * I / mass);

	b2FrictionJointDef jd;
	jd.localAnchorA.SetZero();
	jd.localAnchorB.SetZero();
	jd.bodyA = _ground;
	jd.bodyB = body;
	jd.collideConnected = true;
	jd.maxForce = mass * gravity;
	jd.maxTorque = mass * radius * gravity;

	_world->CreateJoint(&jd);

	return body;
}

b2Body* PhysicsManager::CreateBody(float x, float y, b2BodyType type, b2Shape* shape, bool sensor)
{
	b2BodyDef bd;
	bd.position.Set(x, y);
	bd.type = type;
	bd.allowSleep = false;

	b2Body* body = _world->CreateBody(&bd);

	b2FixtureDef fd;
	fd.shape = shape;
	fd.density = 20.0f;
	fd.friction = 1.0f;
	fd.restitution = 0.0f;
	fd.isSensor = sensor;
	body->CreateFixture(&fd);
	return body;
}

void PhysicsManager::RemoveBody(b2Body* body)
{
	body->GetWorld()->DestroyBody(body);
}

