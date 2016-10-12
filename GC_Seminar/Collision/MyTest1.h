/*
* Copyright (c) 2006-2010 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef MYTEST1_H
#define MYTEST1_H

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h"
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D\Box2D.h>

struct Settings
{
	Settings()
	{
		hz = 60.0f;
		velocityIterations = 8;
		positionIterations = 3;
		drawShapes = true;
		drawJoints = true;
		drawAABBs = false;
		drawContactPoints = false;
		drawContactNormals = false;
		drawContactImpulse = false;
		drawFrictionImpulse = false;
		drawCOMs = false;
		drawStats = false;
		drawProfile = false;
		enableWarmStarting = true;
		enableContinuous = true;
		enableSubStepping = false;
		enableSleep = true;
		pause = false;
		singleStep = false;
	}

	float32 hz;
	int32 velocityIterations;
	int32 positionIterations;
	bool drawShapes;
	bool drawJoints;
	bool drawAABBs;
	bool drawContactPoints;
	bool drawContactNormals;
	bool drawContactImpulse;
	bool drawFrictionImpulse;
	bool drawCOMs;
	bool drawStats;
	bool drawProfile;
	bool enableWarmStarting;
	bool enableContinuous;
	bool enableSubStepping;
	bool enableSleep;
	bool pause;
	bool singleStep;
};

/// This is a test of typical character collision scenarios. This does not
/// show how you should implement a character in your application.
/// Instead this is used to test smooth collision on edge chains.
class MyTest1 : public b2ContactListener
{
public:

	bool testContact(
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


	MyTest1()
	{
		b2Vec2 gravity;
		gravity.Set(0.0f, 0.0f);
		m_world = new b2World(gravity);

		/*{
			
			b2Transform t;
			t.SetIdentity();

			b2BodyDef bd1;
			bd1.position.Set(3.0f, 5.0f);
			bd1.type = b2_dynamicBody;
			bd1.fixedRotation = true;
			bd1.allowSleep = false;

			b2Body* body1 = m_world->CreateBody(&bd1);

			b2CircleShape shape1;
			shape1.m_radius = 0.5f;
			shape1.m_p.Set(0.5f, 0);

			b2FixtureDef fd1;
			fd1.shape = &shape1;
			fd1.density = 20.0f;
			b2Fixture* fixtureB = body1->CreateFixture(&fd1);


			b2BodyDef bd2;
			bd2.position.Set(-13.0f, 8.0f);
			bd2.type = b2_dynamicBody;
			bd2.fixedRotation = true;
			bd2.allowSleep = false;

			b2Body* body2 = m_world->CreateBody(&bd2);

			b2PolygonShape shape2;
			shape2.SetAsBox(0.5f, 0.5f);

			b2FixtureDef fd2;
			fd2.shape = &shape2;
			fd2.density = 20.0f;
			b2Fixture* fixtureA = body2->CreateFixture(&fd2);
			
			


			b2BlockAllocator blockAllocator;
			b2Contact* contact = b2PolygonAndCircleContact::Create(
				fixtureA, 1111,
				fixtureB, 2222, &blockAllocator);
			
			b2Manifold output;
			contact->

			printf("\ncollision : %d", output.pointCount > 0);
			printf("\ntype : %d", output.type);

			for (int i = 0; i < output.pointCount; i++)
			{
				auto p = output.points[i].localPoint;
				
				printf("\npos : (%f, %f)  impulse %f %f",
					p.x, p.y,
					output.points[i].normalImpulse,
					output.points[i].tangentImpulse);
			}

			printf("\nlocal point : %f %f",
				output.localPoint.x,
				output.localPoint.y);

			printf("\nlocal normal : %f %f",
				output.localNormal.x,
				output.localNormal.y);
		}*/



		//m_world->SetGravity(b2Vec2(1, 0));
		// Ground body
		{
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			b2Vec2 points[] =
			{
				b2Vec2(-30.0f, -30.0f),
				b2Vec2(30.0f, -30.0f),
				b2Vec2(30.0f, 30.0f),
				b2Vec2(-30.0f, 30.0f)
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
			shape.Set(b2Vec2(-8.0f, 1.0f), b2Vec2(-6.0f, 1.0f));
			ground->CreateFixture(&shape, 0.0f);
			shape.Set(b2Vec2(-6.0f, 1.0f), b2Vec2(-4.0f, 1.0f));
			ground->CreateFixture(&shape, 0.0f);
			shape.Set(b2Vec2(-4.0f, 1.0f), b2Vec2(-2.0f, 1.0f));
			ground->CreateFixture(&shape, 0.0f);
		}

		// Chain shape
		{
			b2BodyDef bd;
			bd.angle = 0.25f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);

			b2Vec2 vs[4];
			vs[0].Set(5.0f, 7.0f);
			vs[1].Set(6.0f, 8.0f);
			vs[2].Set(7.0f, 8.0f);
			vs[3].Set(8.0f, 7.0f);
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
			shape.SetAsBox(1.0f, 1.0f, b2Vec2(4.0f, 3.0f), 0.0f);
			ground->CreateFixture(&shape, 0.0f);
			shape.SetAsBox(1.0f, 1.0f, b2Vec2(6.0f, 3.0f), 0.0f);
			ground->CreateFixture(&shape, 0.0f);
			shape.SetAsBox(1.0f, 1.0f, b2Vec2(8.0f, 3.0f), 0.0f);
			ground->CreateFixture(&shape, 0.0f);
		}

		// Square made from an edge loop. Collision should be smooth.
		{
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			b2Vec2 vs[4];
			vs[0].Set(-1.0f, 3.0f);
			vs[1].Set(1.0f, 3.0f);
			vs[2].Set(1.0f, 5.0f);
			vs[3].Set(-1.0f, 5.0f);
			b2ChainShape shape;
			shape.CreateLoop(vs, 4);
			ground->CreateFixture(&shape, 0.0f);
		}

		// Edge loop. Collision should be smooth.
		{
			b2BodyDef bd;
			bd.position.Set(-10.0f, 4.0f);
			b2Body* ground = m_world->CreateBody(&bd);

			b2Vec2 vs[10];
			vs[0].Set(0.0f, 0.0f);
			vs[1].Set(6.0f, 0.0f);
			vs[2].Set(6.0f, 2.0f);
			vs[3].Set(4.0f, 1.0f);
			vs[4].Set(2.0f, 2.0f);
			vs[5].Set(0.0f, 2.0f);
			vs[6].Set(-2.0f, 2.0f);
			vs[7].Set(-4.0f, 3.0f);
			vs[8].Set(-6.0f, 2.0f);
			vs[9].Set(-6.0f, 0.0f);
			b2ChainShape shape;
			shape.CreateLoop(vs, 10);
			ground->CreateFixture(&shape, 0.0f);
		}

		// Square character 1
		/*{
			b2BodyDef bd;
			bd.position.Set(-3.0f, 8.0f);
			bd.type = b2_dynamicBody;
			bd.fixedRotation = true;
			bd.allowSleep = false;

			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.5f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;
			body->CreateFixture(&fd);
		}*/

		// Square character 2
		/*{
			b2BodyDef bd;
			bd.position.Set(-5.0f, 5.0f);
			bd.type = b2_dynamicBody;
			bd.fixedRotation = true;
			bd.allowSleep = false;

			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonShape shape;
			shape.SetAsBox(0.25f, 0.25f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;
			body->CreateFixture(&fd);
		}*/

		// Hexagon character
		/*{
			b2BodyDef bd;
			bd.position.Set(-5.0f, 8.0f);
			bd.type = b2_dynamicBody;
			bd.fixedRotation = true;
			bd.allowSleep = false;

			b2Body* body = m_world->CreateBody(&bd);

			float32 angle = 0.0f;
			float32 delta = b2_pi / 3.0f;
			b2Vec2 vertices[6];
			for (int32 i = 0; i < 6; ++i)
			{
				vertices[i].Set(0.5f * cosf(angle), 0.5f * sinf(angle));
				angle += delta;
			}

			b2PolygonShape shape;
			shape.Set(vertices, 6);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;
			body->CreateFixture(&fd);
		}*/

		// Circle character
		/*{
			b2BodyDef bd;
			bd.position.Set(3.0f, 5.0f);
			bd.type = b2_dynamicBody;
			bd.fixedRotation = true;
			bd.allowSleep = false;

			b2Body* body = m_world->CreateBody(&bd);

			b2CircleShape shape;
			shape.m_radius = 3.5f;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;
			body->CreateFixture(&fd);
		}*/

		// Circle character
		/*{
			b2BodyDef bd;
			bd.position.Set(-7.0f, 6.0f);
			bd.type = b2_dynamicBody;
			bd.allowSleep = false;

			b2Body* body = m_world->CreateBody(&bd);

			b2CircleShape shape;
			shape.m_radius = 4.25f;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;
			fd.friction = 1.0f;
			body->CreateFixture(&fd);
		}*/


		// Circle character
		{
			b2BodyDef bd;
			bd.position.Set(-1.0f, 6.0f);
			bd.type = b2_dynamicBody;
			bd.allowSleep = false;

			m_character = m_world->CreateBody(&bd);

			b2CircleShape shape;
			shape.m_radius = 1.25f;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 200.0f;
			fd.friction = 1.0f;
			m_character->CreateFixture(&fd);
		}
	}

	void Step()
	{
		Settings settings;

		b2Vec2 v = m_character->GetLinearVelocity();
		v.x = -15.0f;
		m_character->SetLinearVelocity(v);

		
		uint32 flags = 0;
		flags += settings.drawShapes		* b2Draw::e_shapeBit;
		flags += settings.drawJoints		* b2Draw::e_jointBit;
		flags += settings.drawAABBs			* b2Draw::e_aabbBit;
		flags += settings.drawCOMs			* b2Draw::e_centerOfMassBit;


		m_world->Step(
			settings.hz,
			settings.velocityIterations,
			settings.positionIterations);

		m_world->DrawDebugData();
	}


	b2Body* m_character;
	b2World* m_world;
};

#endif
