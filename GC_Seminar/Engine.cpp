#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsDriver.h"
#include "EntityManager.h"
#include "World.h"
#include "Camera2D.h"
#include "UIManager.h"
#include "Utils.h"

#include "Entity/Hunter.h"

#include <Box2D\Common\b2Draw.h>
#include <chrono>


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

	Button* button = nullptr;

	
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
			_world->getPhysicsMgr()->Explosion(
				b2Vec2(player->getPos().x, player->getPos().y), 5.0f, 100.0f);
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
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&mx, &my);

		switch (inEvent->button.button)
		{
		case SDL_BUTTON_LEFT:
			button = UIManager::instance->trySelect(Vec2(mx, my));
			if (button)
				button->update();

			if (player)
				player->shoot();
			break;

		case SDL_BUTTON_RIGHT:
			if (player)
				player->shootRay();
			break;
		}
		
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mx, &my);
		if (player)
			player->setHeading(
				(Camera2D::instance->screenToWorld(Vec2(mx, my)) 
					- player->getPos()).getNormalized());
		break;
	case SDL_MOUSEWHEEL:
		if (inEvent->wheel.y > 0)
		{
			Camera2D::instance->setScale(
				Camera2D::instance->getScale() * 0.95f);
		}
		else
		{
			Vec2 scale = Camera2D::instance->getScale();
			Camera2D::instance->setScale(scale * 1.05f);
		}

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
		// SDL에서 지원하는 event 확인 방법
		// 어떤 input event가 발생하면 SDL_PollEvent는 true를 리턴하고,
		// event 변수에 상세 내용을 기록한다.
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
				// event에 대한 처리
				handleEvent(&event);
			}
		}
		else
		{
			// 모든 update
			update();
		}
	}

	return event.type;
}


void Engine::update()
{
	std::chrono::duration<double> start = std::chrono::system_clock::now().time_since_epoch();

	// World의 update
	_world->update();
	
	std::chrono::duration<double> end1 = std::chrono::system_clock::now().time_since_epoch();

	//std::cout << "update : " << (end1 - start).count() << std::endl;

	// 새 그래픽 버퍼를 준비한다.
	GraphicsDriver::instance->clear();
	
	// 화면에 그려질 모든 객체들을 그린다.
	_world->render();
	GraphicsDriver::instance->render();
	UIManager::instance->render();

	std::chrono::duration<double> end2 = std::chrono::system_clock::now().time_since_epoch();

	//std::cout << "render : " << (end2 - end1).count() <<  std::endl;

	// 그래픽 버퍼를 화면에 출력한다.
	GraphicsDriver::instance->present();
}
