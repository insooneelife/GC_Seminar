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
class Wall;
class World
{
public:
	enum { InvalidateId = 0 };

	// Entity ���տ� �´� �浹�Ǻ� �� ó��
	static void collide(Hunter& h1, Hunter& h2);
	static void collide(Hunter& h, Projectile& p);
	static void collide(Projectile& h, Prey& p);
	static void collide(Hunter& h, Wall& w);

	// ��� entity�� update ��, garbage ����
	template<class Container>
	static void updateEntity(Container& entities);

	// Entity �����̳� getter && setter
	inline const std::vector<Hunter*>& getHunters() const			{ return _hunters; }
	inline const std::vector<Projectile*>& getProjectiles() const	{ return _projectiles; }
	inline const std::vector<Prey*>& getPreys() const				{ return _preys; }
	inline const std::vector<Wall*>& getWalls() const				{ return _walls; }

	// �÷��̾��� entity�� �����ϱ� ���� getter
	inline Hunter* getPlayerEntity() const							{ return _player_entity; }
	inline void setPlayerEntity(Hunter* const hunter)				{ _player_entity = hunter; }
	
	// ������ id�� ������ �ش�.
	inline unsigned int genID()										{ return _next_validate_id++; }

	World();
	~World();
	
	void createHunter(const Vec2& pos);
	void createProjectile(unsigned int owner_id, const Vec2& pos, const Vec2& heading, int proj_speed);
	void createPrey(const Vec2& pos);
	void createWall(const Vec2& begin, const Vec2& end, const Vec2& heading);

	void update();
	void render();

private:
	std::vector<Hunter*> _hunters;
	std::vector<Projectile*> _projectiles;
	std::vector<Prey*> _preys;
	std::vector<Wall*> _walls;
	std::queue<Entity*> _created_entities;
	
	Hunter* _player_entity;
	unsigned int _next_validate_id;

};