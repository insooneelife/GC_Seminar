#pragma once
//------------------------------------------------------------------------
//
//  Name:		World.h
//
//  Desc:		Class for define all interactive thing in the game world.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <vector>
#include <memory>
#include <queue>
#include "Math\Vec2.h"

class Entity;
class World
{
public:

	const std::vector<std::unique_ptr<Entity> >& getEntities() const;
	Entity* getPlayerEntity() const;

	World();
	~World();

	unsigned int genID() { return _next_validate_id++; }
	void createProjectile(unsigned int owner_id, const Vec2& pos);
	void update();
	void render();

private:
	std::vector<std::unique_ptr<Entity> > _entities;
	std::queue<std::unique_ptr<Entity> > _created_entities;
	Entity* _player_entity;

	unsigned int _next_validate_id;

};