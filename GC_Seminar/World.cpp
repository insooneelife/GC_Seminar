#include <iostream>
#include <Box2D\Box2D.h>
#include "World.h"
#include "EntityManager.h"
#include "Camera2D.h"
#include "Utils.h"
#include "UIManager.h"

#include "Math/Transformations.h"

#include "Entity/GenericEntity.h"
#include "Entity/Unit.h"

namespace
{
	const float kWorldX = 20.0f;
	const float kWorldY = 20.0f;
}

using namespace std;

/*
void World::collide(Hunter& h1, Hunter& h2)
{
	cout << "collide!  Hunter && Hunter" << endl;
}

void World::collide(Hunter& h, Projectile& p)
{
	if (h.getID() == p.getOwnerID())
		return;

	cout << "collide!  Hunter && Projectile" << endl;

	p.setGarbage();

	int damage = h.getDamage();
	EntityManager::instance->dispatchMsg(
		p.getOwnerID(), h.getID(), Message::kDamage, &damage);
}

void World::collide(Projectile& pro, Prey& prey)
{
	cout << "collide!  Projectile && Prey" << endl;
	prey.setGarbage();
	pro.setGarbage();

	int increase = 1;

	EntityManager::instance->dispatchMsg(prey.getID(), pro.getOwnerID(), Message::kIncrease, &increase);
}

void World::collide(Trigger& t, Hunter& h)
{
	cout << "collide!  Trigger && Hunter" << endl;

	if(t.getCondition() == Trigger::Condition::kCollision)
		t.activateOneSelf(h);
}*/


template<class Container>
void World::updateEntity(Container& entities)
{
	// Update entities
	auto e = begin(entities);
	while (e != end(entities))
	{
		// Test for any dead entities and remove them if necessary.
		if (!(*e)->isGarbage())
		{
			(*e)->update();
			++e;
		}
		else
		{
			//if ((*e)->getWorld().getPlayerEntity() != nullptr &&
			//	(*e)->getID() == (*e)->getWorld().getPlayerEntity()->getID())
			//	(*e)->getWorld().setPlayerEntity(nullptr);

			delete *e;
			e = entities.erase(e);
		}
	}
	
}

// World의 생성자에서 모든 entity의 초기화가 이루어진다.
World::World()
	:
	_next_validate_id(1),
	_physics(new PhysicsManager(kWorldX, kWorldY))
{
	auto entity = Unit::create(*this, Vec2(10.0f, 10.0f));
	_entities.push_back(entity);
	auto entity2 = Unit::create(*this, Vec2(10.5f, 10.5f));
	_entities.push_back(entity2);

	// Create player with hunter
	//_player_entity = new Hunter(*this, genID(), Vec2(1.0f, 1.0f));
	//_hunters.push_back(_player_entity);

	// Create hunters
	/*createHunter(Vec2(2.50f, 2.00f));
	createHunter(Vec2(1.50f, 5.00f));
	createHunter(Vec2(3.00f, 4.50f));
	createHunter(Vec2(5.00f, 2.00f));
	createHunter(Vec2(4.50f, 4.00f));
	createHunter(Vec2(10.00f, 6.00f));
	createHunter(Vec2(7.00f, 3.00f));*/
	
	//createTrigger(Vec2(10.0f, 10.0f), Trigger::Condition::kTimer);

	// Create preys
	//for (int i = 0; i < 200; i++)
	//	createPrey(Vec2(random(-kWorldX, kWorldX), random(-kWorldY, kWorldY)));
		
	// Create Structures
	/*for (int i = 0; i < 10; i++)
	{
		int type = random(0, 3);
		createStructure(
			Vec2(random(-kWorldX, kWorldX), random(-kWorldY, kWorldY)),
			random(1.0f, 4.0f),
			type);
	}*/
		
	// Set camera
	Vec2 heading = entity->getHeading();
	Vec2 side = entity->getHeading().getPerp();
	Vec2 pos = entity->getPos();
	Camera2D::instance->setCamera(pos, heading, side, Camera2D::instance->getScale());
}


World::~World()
{}

void World::update()
{

	// If some entities are created, then we first have to push them into queue,
	// and move them to vector after iteration has finished.
	// If entities are inserted into vector when iterating,
	// then it will make a big problem.
	
	/*while (!_created_entities.empty())
	{
		Entity* ent = _created_entities.front();

		if (ent->getType() == Entity::kHunter)
			_hunters.push_back(static_cast<Hunter*>(ent));

		else if (ent->getType() == Entity::kPrey)
			_preys.push_back(static_cast<Prey*>(ent));

		else if (ent->getType() == Entity::kProjectile)
			_projectiles.push_back(static_cast<Projectile*>(ent));

		else if (ent->getType() == Entity::kStructure)
			_structures.push_back(static_cast<Structure*>(ent));

		else if (ent->getType() == Entity::kTrigger)
			_triggers.push_back(static_cast<Trigger*>(ent));

		_created_entities.pop();
	}*/

	while (!_created_entities.empty())
	{
		GenericEntity* ent = _created_entities.front();
		_entities.emplace_back(ent);
		_created_entities.pop();
	}

	_physics->Step();

	// Update entities and delete them if set garbage.
	//updateEntity(_hunters);
	//updateEntity(_projectiles);
	//updateEntity(_preys);
	updateEntity(_entities);

	// Preys must maintain 100 units.
	//int create_num = 100 - _preys.size();
	//while (create_num-- > 0)
	//	createPrey(Vec2(random(-kWorldX, kWorldX), random(-kWorldY, kWorldY)));

	// Camera position setting
	//if (_player_entity) {
	//	Camera2D::instance->setOrigin(_player_entity->getPos());
	//}

	//if (_player_entity)
	//{
	//	UIManager::instance->update(_player_entity->getExp());
	//}

	EntityManager::instance->dispatchDelayedMessages();

}

void World::render()
{
	/*for (auto e : _hunters)
		e->render();

	for (auto p : _projectiles)
		p->render();

	for (auto p : _preys)
		p->render();

	for (auto s : _structures)
		s->render();

	for (auto t : _triggers)
		t->render();*/

	for (auto e : _entities)
		e->render();

	_physics->Render();
}

/*
void World::createHunter(const Vec2& pos)
{
	_created_entities.emplace(new Hunter(*this, genID(), pos));
}

void World::createProjectile(unsigned int owner_id, const Vec2& pos, const Vec2& heading, int proj_speed)
{
	_created_entities.emplace(new Projectile(*this, genID(), owner_id, pos, heading, proj_speed));
}

void World::createPrey(const Vec2& pos)
{
	_created_entities.emplace(new Prey(*this, genID(), pos));
}

void World::createStructure(const Vec2& pos, float radius, int type)
{
	if(type == Structure::StructureType::kCircle)
		_created_entities.emplace(Structure::createCircle(*this, genID(), pos, radius));

	else if (type == Structure::StructureType::kPolygon)
		_created_entities.emplace(Structure::createPolygon(*this, genID(), pos));
	
	else if (type == Structure::StructureType::kAnchor)
		_created_entities.emplace(Structure::createAnchor(*this, genID(), pos, pos + Vec2(2.0f, 0)));
}

void World::createTrigger(const Vec2& pos, int condition)
{
	
	const float wait_time = 5.0f;
	unsigned int id = genID();
	_created_entities.emplace(
		Trigger::createCreateEntityTrigger(
			*this, id, pos, condition, (int)Entity::kHunter, 0, wait_time));
	
}
*/