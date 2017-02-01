#pragma once
//------------------------------------------------------------------------
//
//  Name:		UIManager.h
//
//  Desc:		Utility class for wrapping SDL graphic tools
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>
#include "Math/Vec2.h"



class UIManager
{
public:

	static void staticInit();
	static std::unique_ptr< UIManager > instance;

	~UIManager() {}

	void update(int player_experience);
	void render();

private:
	UIManager();
};
