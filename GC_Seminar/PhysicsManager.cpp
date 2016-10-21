#include "PhysicsManager.h"




bool PhysicsManager::testContact(
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


PhysicsManager::PhysicsManager()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	m_world = new b2World(gravity);
	m_world->SetDebugDraw(GraphicsDriver::instance.get());

	// Ground body
	{
		b2BodyDef bd;
		b2Body* ground = m_world->CreateBody(&bd);

		b2Vec2 points[] =
		{
			b2Vec2(0.0f, 0.0f),
			b2Vec2(1280.0f, 0.0f),
			b2Vec2(1280.0f, 720.0f),
			b2Vec2(0.0f, 720.0f)
		};

		for (int i = 0; i < 4; i++)
		{
			int j = (i + 1) % 4;
			b2EdgeShape shape;
			shape.Set(points[i], points[j]);
			ground->CreateFixture(&shape, 0.0f);
		}
	}

	// Collinear edges with no adjacency information.
	// This shows the problematic case where a box shape can hit
	// an internal vertex.
	{
		b2BodyDef bd;
		b2Body* ground = m_world->CreateBody(&bd);

		b2EdgeShape shape;
		shape.Set(b2Vec2(-80.0f, 10.0f), b2Vec2(-60.0f, 10.0f));
		ground->CreateFixture(&shape, 0.0f);
		shape.Set(b2Vec2(-60.0f, 10.0f), b2Vec2(-40.0f, 10.0f));
		ground->CreateFixture(&shape, 0.0f);
		shape.Set(b2Vec2(-40.0f, 10.0f), b2Vec2(-20.0f, 10.0f));
		ground->CreateFixture(&shape, 0.0f);
	}

	// Chain shape
	{
		b2BodyDef bd;
		bd.angle = 0.25f * b2_pi;
		b2Body* ground = m_world->CreateBody(&bd);

		b2Vec2 vs[4];
		vs[0].Set(50.0f, 70.0f);
		vs[1].Set(60.0f, 80.0f);
		vs[2].Set(70.0f, 80.0f);
		vs[3].Set(80.0f, 70.0f);
		b2ChainShape shape;
		shape.CreateChain(vs, 4);
		ground->CreateFixture(&shape, 0.0f);
	}

	// Square tiles. This shows that adjacency shapes may
	// have non-smooth collision. There is no solution
	// to this problem.
	{
		b2BodyDef bd;
		b2Body* ground = m_world->CreateBody(&bd);

		b2PolygonShape shape;
		shape.SetAsBox(10.0f, 10.0f, b2Vec2(40.0f, 30.0f), 0.0f);
		ground->CreateFixture(&shape, 0.0f);
		shape.SetAsBox(10.0f, 10.0f, b2Vec2(60.0f, 30.0f), 0.0f);
		ground->CreateFixture(&shape, 0.0f);
		shape.SetAsBox(10.0f, 10.0f, b2Vec2(80.0f, 30.0f), 0.0f);
		ground->CreateFixture(&shape, 0.0f);
	}

	// Square made from an edge loop. Collision should be smooth.
	{
		b2BodyDef bd;
		b2Body* ground = m_world->CreateBody(&bd);

		b2Vec2 vs[4];
		vs[0].Set(-10.0f, 30.0f);
		vs[1].Set(10.0f, 30.0f);
		vs[2].Set(10.0f, 50.0f);
		vs[3].Set(-10.0f, 50.0f);
		b2ChainShape shape;
		shape.CreateLoop(vs, 4);
		ground->CreateFixture(&shape, 0.0f);
	}

	// Edge loop. Collision should be smooth.
	{
		b2BodyDef bd;
		bd.position.Set(-100.0f, 40.0f);
		b2Body* ground = m_world->CreateBody(&bd);

		b2Vec2 vs[10];
		vs[0].Set(0.0f, 0.0f);
		vs[1].Set(60.0f, 0.0f);
		vs[2].Set(60.0f, 20.0f);
		vs[3].Set(40.0f, 10.0f);
		vs[4].Set(20.0f, 20.0f);
		vs[5].Set(0.0f, 20.0f);
		vs[6].Set(-20.0f, 20.0f);
		vs[7].Set(-40.0f, 30.0f);
		vs[8].Set(-60.0f, 20.0f);
		vs[9].Set(-60.0f, 0.0f);
		b2ChainShape shape;
		shape.CreateLoop(vs, 10);
		ground->CreateFixture(&shape, 0.0f);
	}

	// Circle character
	{
		b2BodyDef bd;
		bd.position.Set(300.0f, 60.0f);
		bd.type = b2_dynamicBody;
		bd.allowSleep = false;

		m_character = m_world->CreateBody(&bd);

		b2CircleShape shape;
		shape.m_radius = 12.5f;

		b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 200.0f;
		fd.friction = 1.0f;
		m_character->CreateFixture(&fd);
	}
}

void PhysicsManager::Step()
{
	Settings settings;


	uint32 flags = 0;
	flags += settings.drawShapes		* b2Draw::e_shapeBit;
	flags += settings.drawJoints		* b2Draw::e_jointBit;
	flags += settings.drawAABBs			* b2Draw::e_aabbBit;
	flags += settings.drawCOMs			* b2Draw::e_centerOfMassBit;


	m_world->Step(
		settings.hz,
		settings.velocityIterations,
		settings.positionIterations);
}

void PhysicsManager::Render()
{
	m_world->DrawDebugData();
}

