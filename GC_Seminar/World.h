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
#include "Entity.h"

class World
{
public:

	World();
	~World();

	void update();
	void render();

	Entity* getClosestEntityFromPos(Entity& entity, float& distance);

private:
	std::vector<std::unique_ptr<Entity> > _entities;

};