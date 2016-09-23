//------------------------------------------------------------------------
//
//  Name:		World.h
//
//  Desc:		Class for define all interactive thing in the game world.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#pragma once

#include <vector>
#include <memory>

class Entity;
class World
{
public:

	//inline const std::vector<std::unique_ptr<Entity> >& 

	World();
	~World();

	void update();
	void render();

private:
	std::vector<std::unique_ptr<Entity> > _entities;

};