//------------------------------------------------------------------------
//
//  Name:		World.h
//
//  Desc:		Class for define all interactive thing in the game world.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#pragma once

#include <vector>
#include <memory>
#include "Collision\MyTest1.h"

class Entity;
class World
{
public:

	World();
	~World();

	void update();
	void render();

	// �浹ó���� ���� �Լ�
	void checkCollision();

private:
	std::vector<std::unique_ptr<Entity> > _entities;

	MyTest1* test;
};