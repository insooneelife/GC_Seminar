#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsDriver.h"
#include "EntityManager.h"
#include "World.h"
#include "Camera2D.h"
#include "UIManager.h"
#include "Utils.h"

#include "Entity/Hunter.h"

Engine::Engine()
{}

Engine::~Engine()
{}

void Engine::handleEvent(SDL_Event* inEvent)
{
	Hunter* player = _world->getPlayerEntity();
	Vec2 velocity;

	static bool press[255] = { 0 };
	const float distance = 1000;
	const Vec2 left(-1, 0);
	const Vec2 right(1, 0);
	const Vec2 up(0, 1);
	const Vec2 down(0, -1);

	int mx = 0;
	int my = 0;

	Button* but = nullptr;
	
	switch (inEvent->type)
	{
	case SDL_KEYDOWN:
		// Details
		switch (inEvent->key.keysym.sym) 
		{
		case SDLK_a:
			std::cout << "a" << std::endl;
			press[SDLK_a] = true;
			velocity = directionFromMultiKey(press[SDLK_w], press[SDLK_s], left) * distance;
			break;

		case SDLK_d:
			std::cout << "d" << std::endl;
			press[SDLK_d] = true;
			velocity = directionFromMultiKey(press[SDLK_s], press[SDLK_w], right) * distance;
			break;

		case SDLK_w:
			std::cout << "w" << std::endl;
			press[SDLK_w] = true;
			velocity = directionFromMultiKey(press[SDLK_d], press[SDLK_a], up) * distance;
			break;

		case SDLK_s:
			std::cout << "s" << std::endl;
			press[SDLK_s] = true;
			velocity = directionFromMultiKey(press[SDLK_a], press[SDLK_d], down) * distance;
			break;
			
		case SDLK_SPACE:
			break;

		default:
			break;
		}

		if (player)
			player->enterMovingState(player->getPos() + velocity);

		break;
	case SDL_KEYUP:
		// Details
		switch (inEvent->key.keysym.sym)
		{
		case SDLK_a:
			std::cout << "a up" << std::endl;
			press[SDLK_a] = false;
			break;

		case SDLK_d:
			std::cout << "d up" << std::endl;
			press[SDLK_d] = false;
			break;

		case SDLK_w:
			std::cout << "w up" << std::endl;
			press[SDLK_w] = false;
			break;

		case SDLK_s:
			std::cout << "s up" << std::endl;
			press[SDLK_s] = false;
			break;

		case SDLK_SPACE:
			break;

		default:
			break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&mx, &my);

		but = UIManager::instance->trySelect(Vec2(mx, my));
		if(but)
			but->update();

		if (player)
			_world->createProjectile(
				player->getID(),
				player->getPos(),
				player->getHeading(),
				player->getProjSpeed());
		
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mx, &my);
		if (player)
			player->setHeading(
				(Camera2D::instance->screenToWorld(Vec2(mx, my)) 
					- player->getPos()).getNormalized());
		
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

	UIManager::staticInit();
	UIManager::instance->addButton(new Button(*_world, _world->genID(), Vec2(80, 70), "Damage"));
	UIManager::instance->addButton(new Button(*_world, _world->genID(), Vec2(180, 70), "Range"));

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
	UIManager::instance->render();
	GraphicsDriver::instance->present();
}
