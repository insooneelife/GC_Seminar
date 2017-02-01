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

void UIManager::update(int player_experience)
{}

void UIManager::render()
{}