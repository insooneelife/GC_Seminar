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
	switch (inEvent->type)
	{
	case SDL_KEYDOWN:
		std::cout << "SDL_KEYDOWN" << std::endl;
		break;
	case SDL_KEYUP:
		std::cout << "SDL_KEYUP" << std::endl;
		break;
	case SDL_MOUSEBUTTONDOWN:
		std::cout << "SDL_MOUSEBUTTONDOWN" << std::endl;
		break;
	case SDL_MOUSEWHEEL:
		std::cout << inEvent->wheel.x << " " << inEvent->wheel.y << std::endl;

		if (inEvent->wheel.y > 0)
		{
			Camera2D::instance->setScale(
				Vec2(Camera2D::instance->getScale().x + 0.1f,
					Camera2D::instance->getScale().y + 0.1f));
		}
		else
		{
			Camera2D::instance->setScale(
				Vec2(Camera2D::instance->getScale().x - 0.1f,
					Camera2D::instance->getScale().y - 0.1f));
		}
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
