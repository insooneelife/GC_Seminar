#include "World.h"
#include "Entity.h"
#include <iostream>

World::World()
{
	// unique_ptr needs to be initialized by emplace_back.
	_entities.emplace_back(new Entity(*this, 1, Vec2(100.0f, 100.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 2, Vec2(250.0f, 200.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 3, Vec2(150.0f, 500.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 4, Vec2(300.0f, 400.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 5, Vec2(500.0f, 200.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 6, Vec2(455.0f, 400.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 7, Vec2(1000.0f, 600.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 8, Vec2(700.0f, 300.0f), 250.0f));
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