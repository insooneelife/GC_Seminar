#pragma once
//------------------------------------------------------------------------
//
//  Name:   Snake.h
//
//  Desc:   The entity which intakes other entities and grows bigger.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include <vector>
#include <memory>
#include "Entity.h"

class RigidBody;
class Snake : public Entity
{
public:
	enum State
	{
		kIdle,
		kMoving
	};

	inline int getExp() const			{ return _experience; }
	inline void setExp(int exp)			{ _experience = exp; }
	inline bool isPlayer() const		{ return _is_player; }

	Snake(World& world, unsigned int id, const Vec2& pos);

	virtual ~Snake();

	virtual void update();
	virtual void render();
	virtual bool handleMessage(const Message& msg);

	bool checkCollideCircleToBody(Vec2 pos, float radius, Vec2& cpos);

private:
	State _state;
	Vec2 _destination;

	//std::vector<Vec2> _body;
	std::vector<RigidBody*> _body;
	std::vector<Vec2> _destinations;

	int _experience;
	bool _is_player;



};