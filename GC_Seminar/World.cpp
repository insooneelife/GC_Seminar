#include "World.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Math\Transformations.h"
#include "Camera2D.h"
#include <iostream>

World::World()
{
	// unique_ptr needs to be initialized by emplace_back.
	_entities.emplace_back(new Entity(*this, 1, Vec2(100.0f, 300.0f), 155.0f));
	_entities.emplace_back(new Entity(*this, 2, Vec2(250.0f, 200.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 3, Vec2(150.0f, 500.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 4, Vec2(300.0f, 450.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 5, Vec2(500.0f, 200.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 6, Vec2(455.0f, 400.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 7, Vec2(1000.0f, 600.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 8, Vec2(700.0f, 300.0f), 250.0f));


	Entity* ent3 = EntityManager::instance->getEntity(3);
	Entity* ent4 = EntityManager::instance->getEntity(4);

	Vec2 dir = ent4->getPos() - ent3->getPos();
	Vec2 new_heading = dir.getNormalized();

	ent3->setHeading(new_heading);
}


World::~World()
{}

void World::update()
{
	for (auto e = std::begin(_entities); e != std::end(_entities); e++)
	{
		(*e)->update();
	}
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