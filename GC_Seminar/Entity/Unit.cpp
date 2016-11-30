#include <iostream>
#include <sstream>
#include "Unit.h"
#include "../EntityManager.h"
#include "../GraphicsDriver.h"
#include "../PhysicsManager.h"
#include "../World.h"
#include "../TextureManager.h"
#include "../Components/Interfaces.h"
#include "../Components/RenderComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/MoveComponent.h"
#include "../Components/TargetComponent.h"
#include "../Components/AttackComponent.h"
#include "../Components/HitComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Utils.h"


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
	const float kHunterSpeed = 0.01f;

	const float kUnitAttackRange = 2.5f;
	const float kUnitViewRange = 5.0f;

	const int kUnitAttackDamage = 10;
	const int kUnitAttackFrameDelay = 5;
}

Unit* Unit::create(World& world, const Vec2& pos, const std::string& name)
{
	unsigned int id = world.genID();
	Unit* unit = new Unit(world, id, name);

	b2CircleShape circle;
	circle.m_radius = kHunterBodyRadius;

	CollisionComponent* collision = 
		CollisionComponent::create(
			world.getPhysicsMgr()->GetPhysicsWorld(),
			unit,
			&circle,
			b2BodyType::b2_dynamicBody,
			pos,
			false,
			kHunterBodyRadius,
			unit->getType());

	unit->setCollision(collision);

	RenderComponent* rendering = 
		new RenderComponent(*unit, &TextureManager::instance->getTexture("ZealotAttack1"));
	unit->setRendering(rendering);

	MoveComponent* move = 
		new MoveComponent(*unit, kHunterSpeed, Vec2(0, 0), false);
	unit->setMove(move);
	
	TargetComponent* target =
		new TargetComponent(*unit, kUnitAttackRange, kUnitViewRange);
	unit->setTargetting(target);

	AttackComponent* attack =
		new MeleeAttack(*unit, kUnitAttackDamage, kUnitAttackFrameDelay);
	unit->setAttack(attack);

	HitComponent* hit =new HitComponent(*unit, kDefaultMaxHP);
	unit->setHit(hit);

	AnimationComponent* animation = 
		new BaseAnimation(*unit, 9);
	unit->setAnimation(animation);

	return unit;
}

Unit* Unit::createRange(
	World& world, const Vec2& pos, const std::string& name)
{
	auto unit = create(world, pos, name);

	AttackComponent* attack =
		new RangeAttack(*unit, kUnitAttackDamage, kUnitAttackFrameDelay);
	unit->setAttack(attack);
	return unit;
}

Unit::Unit(
	World& world,
	unsigned int id,
	const std::string& name)
	:
	GenericEntity(world, id, GenericEntity::Type::kUnit, name),
	_move(nullptr),
	_rendering(nullptr),
	_collision(nullptr),
	_targetting(nullptr),
	_attack(nullptr),
	_hit(nullptr),
	_animation(nullptr)
{}

Unit::~Unit()
{}

// For ITransformComponent .. 
Vec2 Unit::getPos() const
{
	return Vec2(_collision->getBody()->GetTransform().p.x, _collision->getBody()->GetTransform().p.y);
}

void Unit::setPos(const Vec2& pos)
{
	_collision->getBody()->SetTransform(b2Vec2(pos.x, pos.y), _collision->getBody()->GetAngle());
}

Vec2 Unit::getHeading() const
{
	return Vec2(_collision->getBody()->GetTransform().q.c, _collision->getBody()->GetTransform().q.s);
}

void Unit::setHeading(const Vec2& heading)
{
	b2Rot rot;
	rot.c = heading.x;
	rot.s = heading.y;
	_collision->getBody()->SetTransform(_collision->getBody()->GetTransform().p, rot.GetAngle());
}

b2Transform Unit::getTransform() const
{
	return _collision->getBody()->GetTransform();
}

void Unit::setTransform(const b2Transform& trans)
{
	_collision->getBody()->SetTransform(trans.p, trans.q.GetAngle());
}

// For ICollisionComponent .. 
CollisionComponent& Unit::getCollision() const 
{
	return *_collision; 
}

void Unit::setCollision(CollisionComponent* const collision) 
{
	_collision.reset(collision); 
}

// For IMoveComponent .. 
MoveComponent& Unit::getMove() const 
{
	return *_move; 
}

void Unit::setMove(MoveComponent* const move) 
{
	_move.reset(move); 
}

// For IRenderComponent .. 
RenderComponent& Unit::getRendering() const 
{
	return *_rendering; 
}

void Unit::setRendering(RenderComponent* const render)
{
	_rendering.reset(render); 
}

// For ITargetComponent .. 
TargetComponent& Unit::getTargetting() const
{
	return *_targetting;
}

void Unit::setTargetting(TargetComponent* const target)
{
	_targetting.reset(target);
}

bool Unit::isAlive() const
{
	return
		_fsm.current_state()[0] != 5 &&
		_fsm.current_state()[0] != 6;
}

unsigned int Unit::getID() const
{
	return GenericEntity::getID();
}

// For IAttackComponent .. 
AttackComponent& Unit::getAttack() const
{
	return *_attack;
}

void Unit::setAttack(AttackComponent* const attack)
{
	_attack.reset(attack);
}

// For IHitComponent .. 
HitComponent& Unit::getHit() const
{
	return *_hit;
}

void Unit::setHit(HitComponent* const hit)
{
	_hit.reset(hit);
}

void Unit::setDead()
{
	_fsm.process_event(Fsm::hasToDie<Unit>(*this));
}

// For IAnimationComponent .. 
AnimationComponent& Unit::getAnimation() const 
{
	return *_animation;
}

void Unit::setAnimation(AnimationComponent* const animation)
{
	_animation.reset(animation);
}

std::string Unit::getName() const
{
	return _name;
}


void Unit::update()
{
	_fsm.visit_current_states(boost::ref(*this));
}

void Unit::render()
{
	float radius = kHunterRenderRadius;
	Vec2 pos = getPos();

	std::stringstream ss;
	ss << _id;

	GraphicsDriver::instance->drawCircle(pos, radius);
	GraphicsDriver::instance->drawText(ss.str(), pos);

	Vec2 heading = getHeading();
	Vec2 sidev = getHeading().getPerp() * radius * 0.5f;

	GraphicsDriver::instance->drawLine(pos + sidev, pos - sidev);
	GraphicsDriver::instance->drawLine(pos + sidev, pos + heading * radius * 2);
	GraphicsDriver::instance->drawLine(pos - sidev, pos + heading * radius * 2);
}

bool Unit::handleMessage(const Message& msg)
{
	switch (msg.getMsg())
	{
	case Message::kDamage:
		_hit->takeDamaged(Message::voidToType<int>(msg.getExtraInfo()));
		break;

	case Message::kIncrease:
		//setExp(getExp() + Message::voidToType<int>(msg.getExtraInfo()));
		break;

	case Message::kDecrease:
		break;

	default:
		break;
	}
	return false;
}


/*
Hunter::Hunter(World& world, unsigned int id, const Vec2& pos)
	:
	Entity(world, id, pos, kHunterRenderRadius, Entity::Type::kHunter, GraphicsDriver::black),
	_state(kIdle),
	_experience(5),
	_hp(kDefaultMaxHP),
	_damage(kDefaultDamage),
	_proj_speed(kDefaultProjSpeed),
	_is_player(true),
	_renderable(new RenderComponent(this, TextureManager::sInstance->GetTexture("ZealotAttack1")))
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
	_hp = std::max(0, _hp - damage);
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
			

		for (auto f = body->GetFixtureList(); f; f = f->GetNext())
		{
			std::cout << "hunter pos : " << _pos.x << " " << _pos.y << std::endl;
			b2Vec2 hit;
			_world.getPhysicsMgr()->RayCast(
				f->GetShape(),
				body->GetTransform(),
				b2Vec2(_pos.x, _pos.y),
				b2Vec2(_pos.x + _heading.x * 15.0f, _pos.y + _heading.y * 15.0f), hit);

			GraphicsDriver::instance->addBox2DEdge(_pos, Vec2(_pos.x + _heading.x * 15.0f, _pos.y + _heading.y * 15.0f));
		}


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
*/