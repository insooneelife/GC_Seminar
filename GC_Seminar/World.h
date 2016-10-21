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
#include "PhysicsManager.h"

class Entity;
class World
{
public:

	World();
	~World();

	void update();
	void render();

	// 충돌처리를 위한 함수
	void checkCollision();
	
private:

	std::vector<std::unique_ptr<Entity> > _entities;
	std::unique_ptr<PhysicsManager> _physics;
};