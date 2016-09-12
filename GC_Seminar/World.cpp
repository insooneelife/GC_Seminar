#include "World.h"
#include "Entity.h"
#include <iostream>

World::World()
{
	// unique_ptr needs to be initialized by emplace_back.
	_entities.emplace_back(new Entity(*this, 1, "aa", Vec2(100, 100)));
	_entities.emplace_back(new Entity(*this, 2, "bb", Vec2(200, 200)));
	_entities.emplace_back(new Entity(*this, 3, "cc", Vec2(300, 200)));
	_entities.emplace_back(new Entity(*this, 4, "dd", Vec2(400, 200)));
	_entities.emplace_back(new Entity(*this, 5, "ee", Vec2(500, 200)));
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

Entity* World::getClosestEntityFromPos(Entity& entity, float& distance)
{
	float min_dis = std::numeric_limits<float>::max();
	Entity* min_dis_ent = nullptr;
	for(auto e = std::begin(_entities); e != std::end(_entities); e++)
	{
		if ((*e)->getID() == entity.getID())
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