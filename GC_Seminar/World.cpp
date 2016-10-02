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

World::World()
	:
	_next_validate_id(1)
{
	_player_entity = new Hunter(*this, genID(), Vec2(100.0f, 100.0f));
	_entities.emplace_back(_player_entity);
	_entities.emplace_back(new Hunter(*this, genID(), Vec2(250.0f, 200.0f)));
	//_entities.emplace_back(new Hunter(*this, genID(), Vec2(150.0f, 500.0f)));
	//_entities.emplace_back(new Hunter(*this, genID(), Vec2(300.0f, 450.0f)));
	//_entities.emplace_back(new Hunter(*this, genID(), Vec2(500.0f, 200.0f)));
	//_entities.emplace_back(new Hunter(*this, genID(), Vec2(450.0f, 400.0f)));
	//_entities.emplace_back(new Hunter(*this, genID(), Vec2(1000.0f, 600.0f)));
	//_entities.emplace_back(new Hunter(*this, genID(), Vec2(700.0f, 300.0f)));

	float screenX = Camera2D::instance->getScreenX();
	float screenY = Camera2D::instance->getScreenY();

	for (int i = 0; i < 100; i++)
	{
		_entities.emplace_back(new Prey(*this, genID(), Vec2(random(-screenX, 2 * screenX), random(-screenX, 2 * screenX))));
	}

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
		_entities.emplace_back(std::move(_created_entities.front()));
		_created_entities.pop();
	}

	for (auto e = std::begin(_entities); e != std::end(_entities); e++)
	{
		(*e)->update();
	}

	for (auto e = std::begin(_entities); e != std::end(_entities); e++)
	{
		for (auto o = std::begin(_entities); o != std::end(_entities); o++)
		{
			if ((*e)->getID() == (*o)->getID())
				continue;

			if ((*e)->getType() == Entity::Type::kHunter && (*o)->getType() == Entity::Type::kHunter)
			{
				collide(*static_cast<Hunter*>((*e).get()), *static_cast<Hunter*>((*o).get()));
			}
			else if ((*e)->getType() == Entity::Type::kHunter && (*o)->getType() == Entity::Type::kPrey)
			{
				collide(*static_cast<Hunter*>((*e).get()), *static_cast<Prey*>((*o).get()));
			}
			else if ((*e)->getType() == Entity::Type::kHunter && (*o)->getType() == Entity::Type::kProjectile)
			{
				collide(*static_cast<Hunter*>((*e).get()), *static_cast<Projectile*>((*o).get()));
			}
			else if ((*e)->getType() == Entity::Type::kPrey && (*o)->getType() == Entity::Type::kHunter)
			{
				collide(*static_cast<Hunter*>((*o).get()), *static_cast<Prey*>((*e).get()));
			}
			else if ((*e)->getType() == Entity::Type::kProjectile && (*o)->getType() == Entity::Type::kHunter)
			{
				collide(*static_cast<Hunter*>((*o).get()), *static_cast<Projectile*>((*e).get()));
			}
		}
	}

	Camera2D::instance->setOrigin(_player_entity->getPos());
}

void World::render()
{
	for (auto e = std::begin(_entities); e != std::end(_entities); e++)
	{
		(*e)->render();
	}
}


const std::vector<std::unique_ptr<Entity> >& World::getEntities() const
{
	return _entities;
}

Entity* World::getPlayerEntity() const
{
	return _player_entity;
}

void World::createProjectile(unsigned int owner_id, const Vec2& pos, const Vec2& heading)
{
	_created_entities.emplace(new Projectile(*this, genID(), owner_id, pos, heading));
}