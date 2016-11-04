#include <iostream>
#include <sstream>
#include "Hunter.h"
#include "../EntityManager.h"
#include "../GraphicsDriver.h"
#include "../PhysicsManager.h"
#include "../World.h"
#include "../TextureManager.h"
#include "../Renderable.h"

namespace
{
	const int kUpgradeDamageCost = 10;
	const int kUpgradeRangeCost = 10;

	const int kIncreaseDamage = 1;
	const int kIncreaseRange = 1;

	const int kDefaultMaxHP = 100;
	const int kDefaultDamage = 10;
	const int kDefaultProjSpeed = 15;
	const int kExpFromHunter = 10;

	const float kHunterRenderRadius = 0.25f;
	const float kHunterBodyRadius = 0.20f;
	const float kHunterSpeed = 5.0f;
}

Hunter::Hunter(World& world, unsigned int id, const Vec2& pos)
	:
	Entity(world, id, pos, kHunterRenderRadius, Entity::Type::kHunter, GraphicsDriver::black),
	_state(kIdle),
	_experience(5),
	_hp(kDefaultMaxHP),
	_damage(kDefaultDamage),
	_proj_speed(kDefaultProjSpeed),
	_is_player(true),
	_renderable(new Renderable(this, TextureManager::sInstance->GetTexture("ZealotAttack1")))
{
	b2CircleShape shape;
	shape.m_radius = kHunterBodyRadius;

	_body = _world.getPhysicsMgr()->CreateBody(_pos.x, _pos.y, b2BodyType::b2_dynamicBody, &shape, false);
	_body->SetLinearDamping(2.0f);
	_body->SetUserData(this);
}

Hunter::~Hunter()
{}

bool Hunter::upgradeDamage()
{
	if (_experience - kUpgradeDamageCost < 0)
		return false;

	setExp(getExp() - kUpgradeDamageCost);
	_damage += kIncreaseDamage;

	std::cout << "upgrade damage to : " << _damage << std::endl;
	return true;
}

bool Hunter::upgradeRange()
{
	if (_experience - kUpgradeRangeCost < 0)
		return false;

	setExp(getExp() - kUpgradeRangeCost);
	_proj_speed += kIncreaseRange;

	std::cout << "upgrade range to : " << _proj_speed << std::endl;
	return true;
}

void Hunter::enterMovingState(const Vec2& desti)
{
	_destination = desti;
	_state = State::kMoving;
}

void Hunter::takeDamage(int damage, unsigned int who)
{
	_hp = max(0, _hp - damage);
	if (_hp == 0)
	{
		setGarbage();
		int expr = kExpFromHunter;
		EntityManager::instance->dispatchMsg(_id, who, Message::MsgType::kIncrease, &expr);
	}
		
}

void Hunter::shoot()
{
	_world.createProjectile(_id, _pos + _heading * _radius * 2, _heading, _proj_speed);
}

void Hunter::shootRay()
{
	const float kRange = 500.0f;
	Vec2 shootPos = _pos + _heading * kRange;

	EntityRayCastCallback callback;
	_world.getPhysicsMgr()->QueryRayCast(_pos, shootPos, &callback);

	//check which of these bodies have their center of mass within the blast radius
	std::cout << "callback size : " << callback.foundEntities.size() << std::endl;
	for (int i = 0; i < callback.foundEntities.size(); i++) 
	{
		b2Body* body = callback.foundEntities[i]->getBody();
		b2Vec2 bodyCom = body->GetWorldCenter();
		_world.getPhysicsMgr()->ApplyBlastImpulse(body, b2Vec2(_pos.x, _pos.y), bodyCom, 1000.0f);
			

		//Entity* ent = callback.foundEntities[i];
		//int damage = 100;
		//EntityManager::instance->dispatchMsg(_id, ent->getID(), Message::MsgType::kDamage, &damage);
	}
}

void Hunter::update()
{
	if (_state == State::kIdle)
	{}
	else if (_state == State::kMoving)
	{
		Vec2 velocity = (_destination - _pos).getNormalized() * kHunterSpeed;	
		_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
		
		if (_pos.distance(_destination) < kHunterBodyRadius)
			_state = State::kIdle;
	}

	_pos.set(_body->GetPosition().x, _body->GetPosition().y);
}

void Hunter::render()
{
	std::stringstream ss;
	ss << _id;
	
	GraphicsDriver::instance->drawCircle(_pos, _radius, _color);
	GraphicsDriver::instance->drawText(ss.str(), _pos);

	Vec2 sidev = getSide() * _radius * 0.5f;
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos - sidev, _color);
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos + _heading * _radius * 2, _color);
	GraphicsDriver::instance->drawLine(_pos - sidev, _pos + _heading * _radius * 2, _color);
}


bool Hunter::handleMessage(const Message& msg) 
{
	switch (msg.getMsg())
	{
	case Message::kDamage:
		takeDamage(Message::voidToType<int>(msg.getExtraInfo()), msg.getSender());
		break;

	case Message::kIncrease:
		setExp(getExp() + Message::voidToType<int>(msg.getExtraInfo()));
		break;

	case Message::kDecrease:
		break;

	default:
		break;
	}
	return false; 
}