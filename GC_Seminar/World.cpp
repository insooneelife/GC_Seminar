#include "World.h"
#include "Entity.h"
#include <iostream>

World::World()
{
	// unique_ptr needs to be initialized by emplace_back.
	_entities.emplace_back(new Entity(*this, Vec2(100, 100), 1));
	_entities.emplace_back(new Entity(*this, Vec2(250, 200), 2));
	_entities.emplace_back(new Entity(*this, Vec2(100, 200), 3));
	_entities.emplace_back(new Entity(*this, Vec2(400, 400), 4));
	_entities.emplace_back(new Entity(*this, Vec2(500, 200), 5));
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