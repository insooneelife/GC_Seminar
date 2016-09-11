#include "World.h"
#include "Entity.h"
#include <iostream>

World::World()
{
	// unique_ptr needs to be initialized by emplace_back.
	_entities.emplace_back(new Entity(*this, Vec2(100, 100)));
	_entities.emplace_back(new Entity(*this, Vec2(200, 200)));
	_entities.emplace_back(new Entity(*this, Vec2(300, 200)));
	_entities.emplace_back(new Entity(*this, Vec2(400, 200)));
	_entities.emplace_back(new Entity(*this, Vec2(500, 200)));
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