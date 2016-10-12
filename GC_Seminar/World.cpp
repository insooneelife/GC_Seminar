#include "World.h"
#include "Entity.h"
#include <iostream>
#include <Box2D\Box2D.h>


World::World()
{
	test = new MyTest1();

	// unique_ptr needs to be initialized by emplace_back.
	_entities.emplace_back(new Entity(*this, 1, Vec2(100, 100)));
	_entities.emplace_back(new Entity(*this, 2, Vec2(180, 200)));
	_entities.emplace_back(new Entity(*this, 3, Vec2(50, 100)));
	_entities.emplace_back(new Entity(*this, 4, Vec2(400, 200)));
	_entities.emplace_back(new Entity(*this, 5, Vec2(500, 200)));
	_entities.emplace_back(new Entity(*this, 6, Vec2(150, 200)));
	_entities.emplace_back(new Entity(*this, 7, Vec2(450, 200)));
	_entities.emplace_back(new Entity(*this, 8, Vec2(250, 200)));

	// World가 시작되기 전에 한번 충돌판단을 한다.
	checkCollision();
}

World::~World()
{}

void World::update()
{
	for (auto e = std::begin(_entities); e != std::end(_entities); ++e)
	{
		(*e)->update();
	}
	test->Step();
}

void World::render()
{
	
	for (auto e = std::begin(_entities); e != std::end(_entities); e++)
	{
		(*e)->render();
	}
}

// 충돌판단을 위한 함수
// 이번에는 Box2D를 이용해서 충돌판단을 해보자.
void World::checkCollision()
{
	
}


