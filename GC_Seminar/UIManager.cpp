#include "UIManager.h"
#include "EntityManager.h"
#include "Camera2D.h"
#include <iostream>

std::unique_ptr< UIManager > UIManager::instance = nullptr;

void UIManager::staticInit()
{
	UIManager* new_ui_mgr = new UIManager();
	instance.reset(new_ui_mgr);
}


UIManager::UIManager()
{}

/*
void UIManager::addButton(Button* const button) 
{
	_buttons.push_back(button); 
}

void UIManager::removeButton(Button* const button)
{
	auto iter = std::find(std::begin(_buttons), std::end(_buttons), button);
	if (iter != std::end(_buttons))
		_buttons.erase(iter);
}

Button* UIManager::trySelect(Vec2 pos)
{
	for (auto b : _buttons)
	{
		if (b->contains(pos))
			return b;
	}
	return nullptr;
}

void UIManager::update(int player_experience)
{
	int cost = 10;
	if (player_experience > cost)
	{
		for (auto b : _buttons)
		{
			b->setVisible(true);
		}
	}
	else
	{
		for (auto b : _buttons)
		{
			b->setVisible(false);
		}
	}
}

void UIManager::render()
{
	for (auto b : _buttons)
	{
		b->render();
	}
}*/