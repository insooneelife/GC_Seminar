#include "World.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Math\Transformations.h"
#include "Camera2D.h"
#include <iostream>

World::World()
{
	// unique_ptr needs to be initialized by emplace_back.
	_entities.emplace_back(new Entity(*this, 1, Vec2(100.0f, 100.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 2, Vec2(250.0f, 200.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 3, Vec2(150.0f, 500.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 4, Vec2(300.0f, 450.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 5, Vec2(500.0f, 200.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 6, Vec2(455.0f, 400.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 7, Vec2(1000.0f, 600.0f), 25.0f));
	_entities.emplace_back(new Entity(*this, 8, Vec2(700.0f, 300.0f), 250.0f));

	// (example 2) 1번 entity의 heading을 시계방향으로 30도 회전시키세요.
	Entity* ent1 = EntityManager::instance->getEntity(1);
	Vec2 new_heading = ent1->getHeading().rotateByAngle(Vec2(0, 0), MATH_DEG_TO_RAD(-30));
	ent1->setHeading(new_heading);

	// (example 3) 3번 entity의 heading을 4번 entity를 바라보도록 변환시키세요.
	Entity* ent3 = EntityManager::instance->getEntity(3);
	Entity* ent4 = EntityManager::instance->getEntity(4);
	ent3->setHeading((ent4->getPos() - ent3->getPos()).getNormalized());

	// (example 4) 1번 entity를 4번 entity 방향으로 200만큼 이동시키세요.
	Vec2 direction = (ent4->getPos() - ent1->getPos()).getNormalized();
	ent1->setPos(ent1->getPos() + direction * 200);

	// (example 5) 1번 entity와 3번 entity 사이의 거리를 구하세요.
	std::cout <<"distance between ent1 & ent3 : " 
		<< ent1->getPos().distance(ent3->getPos()) << std::endl;

	// (example 6) 8번 entity와 충돌하는 모든 entity의 id를 출력하세요.
	Entity* ent8 = EntityManager::instance->getEntity(8);
	std::cout << "entities colliding with ent8 : ";
	for (auto it = std::begin(_entities); it != std::end(_entities); ++it)
	{
		if ((*it)->getID() == ent8->getID())
			continue;
		
		if ( (*it)->getPos().distance(ent8->getPos()) < (*it)->getBRadius() + ent8->getBRadius())
		{
			std::cout << (*it)->getID() << " ";
		}
	}
	std::cout << std::endl;

	// (example 7) 6번 entity에 대면하는 모든 entity의 id를 출력하세요.
	Entity* ent6 = EntityManager::instance->getEntity(6);
	std::cout << "entities facing with ent6 : ";
	for (auto it = std::begin(_entities); it != std::end(_entities); ++it)
	{
		if ((*it)->getID() == ent6->getID())
			continue;

		Vec2 toEnt = ((*it)->getPos() - ent6->getPos()).getNormalized();
		
		if (ent6->getHeading().dot(toEnt) > 0)
			std::cout << (*it)->getID() << " ";
	}
	std::cout << std::endl;


	// (example 8) 6번 entity를 기준으로 세계 공간을 지역 공간으로 변환시키세요.

	ent6->setHeading(Vec2(-1, 0));
	Vec2 heading = ent6->getHeading();
	Vec2 side = ent6->getSide();
	Vec2 pos = ent6->getPos();

	//Camera2D::instance->setCamera(pos, heading, side);

	/*for (auto it = std::begin(_entities); it != std::end(_entities); ++it)
	{
		Vec2 new_pos = pointToLocalSpace((*it)->getPos(), heading, side, pos);
		Vec2 new_vec = vectorToLocalSpace((*it)->getHeading(), heading, side);
		(*it)->setPos(new_pos);
		(*it)->setHeading(new_vec);
	}*/
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