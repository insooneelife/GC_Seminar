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
#include <SDL\SDL_ttf.h>
#include <memory>
#include "Math\Vec2.h"
#include "Entity\Button.h"



class UIManager
{
public:

	static void staticInit();
	static std::unique_ptr< UIManager > instance;

	~UIManager() {}

	void addButton(Button* const button);
	void removeButton(Button* const button);

	Button* trySelect(Vec2 pos);
	void update() {}
	void render();


private:
	UIManager();

	std::vector<Button*> _buttons;

};
