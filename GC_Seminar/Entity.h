#pragma once
//------------------------------------------------------------------------
//
//  Name:   Entity.h
//
//  Desc:   Base class for all entities in the game.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------


#include "Math\Vec2.h"
#include "StateMachine\StateMachine.h"
#include "Behaviors\Movable.h"
#include "Behaviors\TargetSystem.h"
#include "Behaviors\Hittable.h"
#include "Behaviors\AttackSystem.h"

#include <memory>
#include <string>

class Message;
class World;
class Entity
{
public:
	typedef msm::back::state_machine< Fsm_<Entity> > Fsm;

	enum EntityMask
	{
		kNone = 0,
		kEntity = 1,
		kStructure = 2
	};

	// Static factory method for easy creating at entity
	static Entity* createUnit(World& world, const Vec2& pos);
	static Entity* createStructure(World& world, const Vec2& pos);

	inline World& getWorld() const		{ return _world; }
	inline unsigned int getID() const	{ return _id; }
	inline std::string getName() const	{ return _name; }
	inline float getBRadius() const		{ return _bounding_radius; }
	inline int getType() const			{ return _type; }

	// Garbage tag is useful to remove any dead entities from world
	inline bool isGarbage() const		{ return _is_garbage; }
	inline void setGarbage()			{ _is_garbage = true; }

	// State machine
	inline Fsm& getFsm()				{ return *_fsm; }
	inline void setFsm(Fsm* fsm)		{ _fsm.reset(fsm); }

	// For movement
	inline Movable& getMove() const				{ return *_move; };
	inline void setMove(Movable* const move)	{ _move.reset(move); }
	inline Vec2 getPos() const					{ return _pos; };
	inline void setPos(const Vec2& pos)			{ _pos = pos; };
	inline Vec2 getHeading() const				{ return _heading; };
	inline void setHeading(const Vec2& heading)	{ _heading = heading; };

	// For targeting
	inline TargetSystem& getTargetSys() const				{ return *_targetSys; }
	inline void setTargetSys(TargetSystem* const target)	{ _targetSys.reset(target); }

	// For hittable
	inline Hittable& getHittable() const				{ return *_hit; }
	inline void setHittable(Hittable* const hit)		{ _hit.reset(hit); }
	inline bool isAlive() const							{ return _alive; }
	inline void setAlive(bool alive)					{ _alive = alive; }

	// For attacking
	inline AttackSystem& getAttackSys() const				{ return *_attackSys; }
	inline void setAttackSys(AttackSystem* const attack)	{ _attackSys.reset(attack); }

	// For message handling
	virtual bool handleMessage(const Message& msg);

	virtual ~Entity();

	virtual void update();
	virtual void render();

private:
	Entity(const Entity&) = delete; // no copies
	Entity& operator=(const Entity&) = delete; // no self-assignments
	Entity() = delete;

	Entity(
		World& world,
		unsigned int id,
		const std::string& name,
		const Vec2& pos,
		float bounding_radius,
		int type);

protected:

	World& _world;
	std::unique_ptr<Fsm> _fsm;

	// For IMovable
	std::unique_ptr<Movable> _move;
	Vec2 _pos;
	Vec2 _heading;

	// For ITargetable
	std::unique_ptr<TargetSystem> _targetSys;

	// For IHittable
	std::unique_ptr<Hittable> _hit;

	// For IAttackable
	std::unique_ptr<AttackSystem> _attackSys;

	unsigned int		_id;
	std::string			_name;
	float				_bounding_radius;
	bool				_is_garbage;
	bool				_alive;
	int					_type;
};