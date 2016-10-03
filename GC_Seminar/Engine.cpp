#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsDriver.h"
#include "EntityManager.h"
#include "World.h"
#include "Camera2D.h"

#include "Entity/Hunter.h"

Engine::Engine()
{}

Engine::~Engine()
{}

void Engine::handleEvent(SDL_Event* inEvent)
{
	Vec2 player_pos = _world->getPlayerEntity()->getPos();
	int mx = 0;
	int my = 0;
	
	switch (inEvent->type)
	{
	case SDL_KEYDOWN:
		// Details
		switch (inEvent->key.keysym.sym) 
		{
		case SDLK_LEFT:
			std::cout << "L" << std::endl;
			break;
		case SDLK_RIGHT:
			std::cout << "R" << std::endl;
			break;
		case SDLK_UP:
			std::cout << "U" << std::endl;
			break;
		case SDLK_DOWN:
			std::cout << "D" << std::endl;
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
		SDL_GetMouseState(&mx, &my);
		_world->getPlayerEntity()->enterMovingState(Camera2D::instance->screenToWorld(Vec2(mx, my)));
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
