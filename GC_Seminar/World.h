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
class Hunter;
class Prey;
class Projectile;
class World
{
public:
	static void collide(Hunter& h1, Hunter& h2);
	static void collide(Hunter& h1, Projectile& h2);
	static void collide(Hunter& h1, Prey& h2);
	template<class Container>
	static void updateEntity(Container& entities);

	inline const std::vector<Hunter*>& getHunters() const			{ return _hunters; }
	inline const std::vector<Projectile*>& getProjectiles() const	{ return _projectiles; }
	inline const std::vector<Prey*>& getPreys() const				{ return _preys; }
	inline Hunter* getPlayerEntity() const							{ return _player_entity; }
	inline unsigned int genID()										{ return _next_validate_id++; }

	World();
	~World();
	
	void createHunter(const Vec2& pos);
	void createProjectile(unsigned int owner_id, const Vec2& pos, const Vec2& heading);
	void createPrey(const Vec2& pos);

	void update();
	void render();

private:
	std::vector<Hunter*> _hunters;
	std::vector<Projectile*> _projectiles;
	std::vector<Prey*> _preys;
	std::queue<Entity*> _created_entities;
	
	Hunter* _player_entity;
	unsigned int _next_validate_id;

};