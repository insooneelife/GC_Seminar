#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsDriver.h"
#include "Entity.h"
#include "EntityManager.h"
#include "World.h"
#include "Camera2D.h"

Engine::Engine()
{}

Engine::~Engine()
{}

void Engine::handleEvent(SDL_Event* inEvent)
{
	Vec2 player_pos = _world->getPlayerEntity()->getPos();
	
	switch (inEvent->type)
	{
	case SDL_KEYDOWN:
		// Details
		switch (inEvent->key.keysym.sym) 
		{
		case SDLK_LEFT:
			std::cout << "L" << std::endl;
			_world->getPlayerEntity()->setPos(player_pos + Vec2(-10, 0));
			_world->getPlayerEntity()->setHeading(Vec2(-1, 0));
			break;
		case SDLK_RIGHT:
			std::cout << "R" << std::endl;
			_world->getPlayerEntity()->setPos(player_pos + Vec2(10, 0));
			_world->getPlayerEntity()->setHeading(Vec2(1, 0));
			break;
		case SDLK_UP:
			std::cout << "U" << std::endl;
			_world->getPlayerEntity()->setPos(player_pos + Vec2(0, 10));
			_world->getPlayerEntity()->setHeading(Vec2(0, 1));
			break;
		case SDLK_DOWN:
			std::cout << "D" << std::endl;
			_world->getPlayerEntity()->setPos(player_pos + Vec2(0, -10));
			_world->getPlayerEntity()->setHeading(Vec2(0, -1));
			break;
			
		case SDLK_SPACE:
			_world->createProjectile(
				_world->getPlayerEntity()->getID(),
				_world->getPlayerEntity()->getPos(),
				_world->getPlayerEntity()->getHeading());
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		std::cout << "SDL_KEYUP" << std::endl;
		break;
	case SDL_MOUSEBUTTONDOWN:
		std::cout << "SDL_MOUSEBUTTONDOWN" << std::endl;
		break;
	default:
		break;
	}
}

bool Engine::init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	if (!WindowManager::staticInit())
	{
		return false;
	}

	if (!GraphicsDriver::staticInit(WindowManager::instance->getMainWindow()))
	{
		return false;
	}
	
	Camera2D::staticInit(1280, 720);

	EntityManager::staticInit();

	_world.reset(new World());
	return true;
}

int Engine::run()
{
	// Main message loop
	bool quit = false;
	SDL_Event event;
	memset(&event, 0, sizeof(SDL_Event));

	while (!quit)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT ||
				(event.type == SDL_WINDOWEVENT &&
					event.window.event == SDL_WINDOWEVENT_CLOSE))
			{
				quit = true;
			}
			else
			{
				handleEvent(&event);
			}
		}
		else
		{
			update();
		}
	}

	return event.type;
}



void Engine::update()
{
	_world->update();
	GraphicsDriver::instance->clear();
	_world->render();
	GraphicsDriver::instance->render();
	GraphicsDriver::instance->present();
}
