#include "World.h"
#include "Hunter.h"
#include "Prey.h"
#include "Projectile.h"
#include "EntityManager.h"
#include "Math\Transformations.h"
#include "Camera2D.h"
#include "Utils.h"
#include <iostream>
using namespace std;

void World::collide(Hunter& h1, Hunter& h2)
{
	if ((h1.getPos().distance(h2.getPos()) < h1.getBRadius() + h2.getBRadius()))
	{
		cout << "collide!  Hunter && Hunter" << endl;
	}
}

void World::collide(Hunter& h, Projectile& p)
{
	if ((h.getPos().distance(p.getPos()) < h.getBRadius() + p.getBRadius()))
	{
		cout << "collide!  Hunter && Projectile" << endl;
	}
}

void World::collide(Hunter& h, Prey& p)
{
	if ((h.getPos().distance(p.getPos()) < h.getBRadius() + p.getBRadius()))
	{
		cout << "collide!  Hunter && Prey" << endl;
	}
}

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
			delete *e;
			e = entities.erase(e);
		}
	}
	
}

World::World()
	:
	_next_validate_id(1)
{
	_player_entity = new Hunter(*this, genID(), Vec2(100.0f, 100.0f));
	_hunters.push_back(_player_entity);

	createHunter(Vec2(250.0f, 200.0f));
	createHunter(Vec2(150.0f, 500.0f));
	createHunter(Vec2(300.0f, 450.0f));
	createHunter(Vec2(500.0f, 200.0f));
	createHunter(Vec2(450.0f, 400.0f));
	createHunter(Vec2(1000.0f, 600.0f));
	createHunter(Vec2(700.0f, 300.0f));

	float screenX = Camera2D::instance->getScreenX();
	float screenY = Camera2D::instance->getScreenY();

	for (int i = 0; i < 100; i++)
		createPrey(Vec2(random(-screenX, 2 * screenX), random(-screenX, 2 * screenX)));

	Vec2 heading = _player_entity->getHeading();
	Vec2 side = _player_entity->getSide();
	Vec2 pos = _player_entity->getPos();
	Camera2D::instance->setCamera(pos, heading, side);
}


World::~World()
{}

void World::update()
{
	while (!_created_entities.empty())
	{
		Entity* ent = _created_entities.front();

		if (ent->getType() == Entity::kHunter) 
		{
			_hunters.push_back(static_cast<Hunter*>(ent));
		}
		else if (ent->getType() == Entity::kPrey)
		{
			_preys.push_back(static_cast<Prey*>(ent));
		}
		else if (ent->getType() == Entity::kProjectile)
		{
			_projectiles.push_back(static_cast<Projectile*>(ent));
		}
		_created_entities.pop();
	}

	updateEntity(_hunters);
	updateEntity(_projectiles);
	updateEntity(_preys);


	for (auto h1 : _hunters)
		for (auto h2 : _hunters)
			if (h1->getID() != h2->getID())
				collide(*h1, *h2);

	for (auto h : _hunters)
		for (auto p : _projectiles)
				collide(*h, *p);

	for (auto h : _hunters)
		for (auto p : _preys)
				collide(*h, *p);

	Camera2D::instance->setOrigin(_player_entity->getPos());
}

void World::render()
{
	for (auto e = begin(_hunters); e != end(_hunters); e++)
		(*e)->render();

	for (auto p = begin(_projectiles); p != end(_projectiles); p++)
		(*p)->render();

	for (auto p = begin(_preys); p != end(_preys); p++)
		(*p)->render();
}


void World::createHunter(const Vec2& pos)
{
	_created_entities.emplace(new Hunter(*this, genID(), pos));
}

void World::createProjectile(unsigned int owner_id, const Vec2& pos, const Vec2& heading)
{
	_created_entities.emplace(new Projectile(*this, genID(), owner_id, pos, heading));
}

void World::createPrey(const Vec2& pos)
{
	_created_entities.emplace(new Prey(*this, genID(), pos));
}