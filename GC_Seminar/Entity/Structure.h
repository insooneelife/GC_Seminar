#pragma once
//------------------------------------------------------------------------
//
//  Name:   Structure.h
//
//  Desc:   
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "Entity.h"

class Structure : public Entity
{
public:

	enum StructureType
	{
		kCircle,
		kPolygon,
		kAnchor
	};

	static Structure* createCircle(World& world, unsigned int id, const Vec2& pos, float radius);
	static Structure* createPolygon(World& world, unsigned int id, const Vec2& pos);
	static Structure* createAnchor(World& world, unsigned int id, const Vec2& begin, const Vec2& end);

	inline StructureType getStructureType() const { return _structure_type; }

	virtual ~Structure();
	virtual void update();
	virtual void render();

private:

	Structure(
		World& world,
		unsigned int id,
		const Vec2& pos,
		StructureType type,
		b2Body* body);

	StructureType _structure_type;
};