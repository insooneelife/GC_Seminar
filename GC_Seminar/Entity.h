//------------------------------------------------------------------------
//
//  Name:   Entity.h
//
//  Desc:   Base class for all entities in the game.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#pragma once

#include "Math\Vec2.h"
#include "StateMachine\StateMachine.h"
#include "Behaviors\Interfaces.h"
#include "Behaviors\Movable.h"
#include "Behaviors\TargetSystem.h"
#include "Behaviors\Hittable.h"
#include "Behaviors\AttackSystem.h"

#include <memory>
#include <string>


class World;
class Entity : IMovable, IAttackable, IHittable
{
public:
	typedef msm::back::state_machine< Fsm_<Entity> > Fsm;

	enum EntityMask
	{
		kEntity = 0x00000000000001
	};

	static Entity* create(World& world, const Vec2& pos);
	static void addMask(unsigned int& src, unsigned int mask)		{ src |= mask; }
	static bool isMasked(unsigned int src, unsigned int mask)		{ return ((src & mask) == mask); }
	static void removeMask(unsigned int& src, unsigned int mask)	{ if (isMasked(src, mask)) src ^= mask; }

	inline World& getWorld() const		{ return _world; }
	inline unsigned int getID() const	{ return _id; }
	inline unsigned int getMask() const	{ return _mask; }
	inline std::string getName() const	{ return _name; }
	inline bool isGarbage() const		{ return _is_garbage; }
	inline void setGarbage()			{ _is_garbage = true; }
	inline float getBRadius() const		{ return _bounding_radius; }

	// State Machine
	inline Fsm& getFsm()				{ return *_fsm; }
	inline void setFsm(Fsm* fsm)		{ _fsm.reset(fsm); }

	// For IMovable
	virtual Movable& getMove() const				{ return *_move; };
	virtual void setMove(Movable* const move)		{ _move.reset(move); }
	virtual Vec2 getPos() const						{ return _pos; };
	virtual void setPos(const Vec2& pos)			{ _pos = pos; };
	virtual Vec2 getHeading() const					{ return _heading; };
	virtual void setHeading(const Vec2& heading)	{ _heading = heading; };

	// For ITargetable
	virtual TargetSystem& getTargetSys() const				{ return *_targetSys; }
	virtual void setTargetSys(TargetSystem* const target)	{ _targetSys.reset(target); }

	// For IMessageHandler
	virtual bool handleMessage(const Message& msg);

	// For IHittable
	virtual Hittable& getHittable() const				{ return *_hit; }
	virtual void setHittable(Hittable* const hit)		{ _hit.reset(hit); }
	virtual bool isAlive() const 
	{
		return
			_fsm->current_state()[0] != 5 &&
			_fsm->current_state()[0] != 6;
	}

	// For IAttackable
	virtual AttackSystem& getAttackSys() const				{ return *_attackSys; }
	virtual void setAttackSys(AttackSystem* const attack)	{ _attackSys.reset(attack); }

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
		float bounding_radius);

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
	unsigned int		_mask;
	std::string			_name;
	bool				_is_garbage;
	float				_bounding_radius;
};