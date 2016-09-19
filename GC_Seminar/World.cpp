#include "World.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Utils.h"
#include <iostream>

World::World()
{
	for (int i = 0; i < 15; i++)
	{
		float x = random(0, 1280);
		float y = random(0, 720);
		createEntity(Vec2(x, y), "Unit");
	}

	for (int i = 0; i < 5; i++)
	{
		float x = random(0, 1280);
		float y = random(0, 720);
		createEntity(Vec2(x, y), "Structure");
	}
}

World::~World()
{}

void World::update()
{
	// Update entities
	auto e = std::begin(_entities);
	while (e != std::end(_entities))
	{
		// Test for any dead entities and remove them if necessary.
		if (!(*e)->isGarbage())
		{
			(*e)->update();
			++e;
		}
		else
		{
			(*e).reset();
			e = _entities.erase(e);
		}
	}
}

void World::render()
{
	for (auto e = std::begin(_entities); e != std::end(_entities); e++)
	{
		(*e)->render();
	}
}

void World::createEntity(const Vec2& pos, const std::string& type)
{
	if (type == "Unit")
	{
		_entities.emplace_back(Entity::createUnit(*this, pos));
	}
	else if (type == "Structure")
	{
		_entities.emplace_back(Entity::createStructure(*this, pos));
	}
}


Entity* World::getClosestEntityFromPos(Entity& entity, float& distance)
{
	float min_dis = std::numeric_limits<float>::max();
	Entity* min_dis_ent = nullptr;
	for(auto e = std::begin(_entities); e != std::end(_entities); e++)
	{
		//if ((*e)->getID() == entity.getID() || !(*e)->isAlive())
		if ((*e)->getID() == entity.getID() ||
			!(*e)->isAlive() ||
			(*e)->getType() == Entity::kStructure)
			continue;

		float dis = (*e)->getPos().distance(entity.getPos());
		if (dis < min_dis)
		{
			min_dis = dis;
			min_dis_ent = (*e).get();
		}
	}
	distance = min_dis;
	return min_dis_ent;
}