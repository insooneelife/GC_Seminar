#include <iostream>
#include "World.h"
#include "EntityManager.h"
#include "Camera2D.h"
#include "Utils.h"
#include "UIManager.h"

#include "Math\Transformations.h"

#include "Entity/Hunter.h"
#include "Entity/Prey.h"
#include "Entity/Projectile.h"
#include "Entity/Wall.h"

using namespace std;

void World::collide(Hunter& h1, Hunter& h2)
{
	if ((h1.getPos().distance(h2.getPos()) < h1.getBRadius() + h2.getBRadius()))
	{
		cout << "collide!  Hunter && Hunter" << endl;
		/*if (h1.getBRadius() > h2.getBRadius())
		{
			h1.increase(h2.getIntake());
			h2.setGarbage();
		}
		else if (h1.getBRadius() < h2.getBRadius())
		{
			h2.increase(h1.getIntake());
			h1.setGarbage();
		}
		else
		{}*/
	}
}

void World::collide(Hunter& h, Projectile& p)
{
	if ((h.getPos().distance(p.getPos()) < h.getBRadius() + p.getBRadius()))
	{
		cout << "collide!  Hunter && Projectile" << endl;

		p.setGarbage();

		int damage = h.getDamage();
		EntityManager::instance->dispatchMsg(
			p.getOwnerID(), h.getID(), Message::kDamage, &damage);
	}
}

void World::collide(Projectile& pro, Prey& prey)
{
	if ((pro.getPos().distance(prey.getPos()) < pro.getBRadius() + prey.getBRadius()))
	{
		cout << "collide!  Projectile && Prey" << endl;
		prey.setGarbage();
		pro.setGarbage();

		int increase = 1;
		EntityManager::instance->dispatchMsg(
			prey.getID(), pro.getOwnerID(), Message::kIncrease, &increase);

	}
}

void World::collide(Hunter& h, Wall& w)
{
	if (segmentCircleOverlap(w.getBegin(), w.getEnd(), h.getPos(), h.getBRadius()))
	{
		cout << "collide!  Hunter && Wall" << endl;

		float distance = sqrt(distToSegmentSq(w.getBegin(), w.getEnd(), h.getPos()));
		Vec2 force = w.getHeading() * distance;
		h.setPos(h.getPos() + force);
	}
}





template<class Container>
void World::updateEntity(Container& entities)
{
	// Update entities
	auto e = begin(entities);
	while (e != end(entities))
	{
		// Test for any dead entities and remove them if necessary.
		if (!(*e)->isGarbage())
		{
			(*e)->update();
			++e;
		}
		else
		{
			if ((*e)->getWorld().getPlayerEntity() != nullptr &&
				(*e)->getID() == (*e)->getWorld().getPlayerEntity()->getID())
				(*e)->getWorld().setPlayerEntity(nullptr);

			delete *e;
			e = entities.erase(e);
		}
	}
	
}

// World의 생성자에서 모든 entity의 초기화가 이루어진다.
World::World(float width, float height)
	:
	_next_validate_id(1),
	_width(width),
	_height(height)
{
	// Create player with hunter
	_player_entity = new Hunter(*this, genID(), Vec2(100.0f, 100.0f));
	_hunters.push_back(_player_entity);

	// Create hunters
	createHunter(Vec2(250.0f, 200.0f));
	createHunter(Vec2(150.0f, 500.0f));
	createHunter(Vec2(300.0f, 450.0f));
	createHunter(Vec2(500.0f, 200.0f));
	createHunter(Vec2(450.0f, 400.0f));
	createHunter(Vec2(1000.0f, 600.0f));
	createHunter(Vec2(700.0f, 300.0f));

	// Create preys
	for (int i = 0; i < 100; i++)
		createPrey(Vec2(random(-width / 2, width / 2), random(-height / 2, height / 2)));

	// Create walls
	float dummy = 100.0f;
	Vec2 bot_left(-(width + dummy) / 2, -(height + dummy) / 2);
	Vec2 bot_right((width + dummy) / 2, -(height + dummy) / 2);
	Vec2 top_left(-(width + dummy) / 2, (height + dummy) / 2);
	Vec2 top_right((width + dummy) / 2, (height + dummy) / 2);

	createWall(bot_left, bot_right, (bot_right - bot_left).getNormalized().getPerp());
	createWall(bot_right, top_right, (top_right - bot_right).getNormalized().getPerp());
	createWall(top_right, top_left, (top_left - top_right).getNormalized().getPerp());
	createWall(top_left, bot_left, (bot_left - top_left).getNormalized().getPerp());

	// Set camera
	Vec2 heading = _player_entity->getHeading();
	Vec2 side = _player_entity->getSide();
	Vec2 pos = _player_entity->getPos();
	Camera2D::instance->setCamera(pos, heading, side, Camera2D::instance->getScale());
}


World::~World()
{}

void World::update()
{
	// If some entities are created, then we first have to push them into queue,
	// and move them to vector after iteration has finished.
	// If entities are inserted into vector when iterating,
	// then it will make a big problem.
	while (!_created_entities.empty())
	{
		Entity* ent = _created_entities.front();

		if (ent->getType() == Entity::kHunter)
			_hunters.push_back(static_cast<Hunter*>(ent));

		else if (ent->getType() == Entity::kPrey)
			_preys.push_back(static_cast<Prey*>(ent));

		else if (ent->getType() == Entity::kProjectile)
			_projectiles.push_back(static_cast<Projectile*>(ent));

		else if (ent->getType() == Entity::kWall)
			_walls.push_back(static_cast<Wall*>(ent));

		_created_entities.pop();
	}
	
	// Update entities and delete them if set garbage.
	updateEntity(_hunters);
	updateEntity(_projectiles);
	updateEntity(_preys);


	// Preys must maintain 100 units.
	float screenX = Camera2D::instance->getScreenX();
	float screenY = Camera2D::instance->getScreenY();
	int create_num = 100 - _preys.size();
	while (create_num-- > 0)
		createPrey(Vec2(random(-_width / 2, _width / 2), random(-_height / 2, _height / 2)));


	// Process collide between entities.
	for (auto h1 : _hunters)
		for (auto h2 : _hunters)
			if (h1->getID() != h2->getID())
				collide(*h1, *h2);

	for (auto h : _hunters)
		for (auto p : _projectiles)
			if (h->getID() != p->getOwnerID())
			collide(*h, *p);

	for (auto pro : _projectiles)
		for (auto p : _preys)
			collide(*pro, *p);

	for (auto h : _hunters)
		for (auto w : _walls)
			collide(*h, *w);

	// Camera position setting
	if (_player_entity) {
		Camera2D::instance->setOrigin(_player_entity->getPos());
		/*Camera2D::instance->setCamera(
			_player_entity->getPos(),
			_player_entity->getHeading(),
			_player_entity->getSide(),
			Camera2D::instance->getScale());*/
	}

	if (_player_entity)
	{
		UIManager::instance->update(_player_entity->getExp());
	}

	
}

void World::render()
{
	for (auto e : _hunters)
		e->render();

	for (auto p : _projectiles)
		p->render();

	for (auto  p: _preys)
		p->render();

	for (auto p : _walls)
		p->render();
}


void World::createHunter(const Vec2& pos)
{
	_created_entities.emplace(new Hunter(*this, genID(), pos));
}

void World::createProjectile(unsigned int owner_id, const Vec2& pos, const Vec2& heading, int proj_speed)
{
	_created_entities.emplace(new Projectile(*this, genID(), owner_id, pos, heading, proj_speed));
}

void World::createPrey(const Vec2& pos)
{
	_created_entities.emplace(new Prey(*this, genID(), pos));
}

void World::createWall(const Vec2& begin, const Vec2& end, const Vec2& heading)
{
	_created_entities.emplace(new Wall(*this, genID(), begin, end, heading));
}