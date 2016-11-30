#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsDriver.h"
#include "EntityManager.h"
#include "World.h"
#include "Camera2D.h"
#include "UIManager.h"
#include "TextureManager.h"
#include "Utils.h"

#include <Box2D/Common/b2Draw.h>
#include <chrono>


Engine::Engine()
{}

Engine::~Engine()
{}

void Engine::handleEvent(SDL_Event* inEvent)
{
	//Hunter* player = _world->getPlayerEntity();
	Vec2 velocity;

	static bool press[255] = { 0 };
	const float distance = 1000;

	const Vec2 left(-1, 0);
	const Vec2 right(1, 0);
	const Vec2 up(0, 1);
	const Vec2 down(0, -1);

	int mx = 0;
	int my = 0;

	//Button* button = nullptr;

	
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

		case SDLK_q:
			break;
			
		case SDLK_SPACE:
			break;

		default:
			break;
		}

		Camera2D::instance->setMoveVelocity(velocity.getNormalized() / 10);

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
			
			//button = UIManager::instance->trySelect(Vec2(mx, my));
			//if (button)
			//	button->update();

			//if (player)
			//	player->shoot();
			break;

		case SDL_BUTTON_RIGHT:
			//if (player)
			//	player->shootRay();
			break;
		}
		
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mx, &my);
		//if (player)
			//player->setHeading(
			//	(Camera2D::instance->screenToWorld(Vec2(mx, my)) 
			//		- player->getPos()).getNormalized());
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
	TextureManager::staticInit();

	_world.reset(new World());

	//UIManager::staticInit();
	//UIManager::instance->addButton(new Button(*_world, _world->genID(), Vec2(80, 70), "Damage"));
	//UIManager::instance->addButton(new Button(*_world, _world->genID(), Vec2(180, 70), "Range"));

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
	
	// now() 함수를 통해 현재 시간값을 구한다.
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	// World의 update
	_world->update();
	Camera2D::instance->update();

	// 새 그래픽 버퍼를 준비한다.
	GraphicsDriver::instance->clear();
	
	// 화면에 그려질 모든 객체들을 그린다.
	_world->render();
	GraphicsDriver::instance->render();
	UIManager::instance->render();

	// 그래픽 버퍼를 화면에 출력한다.
	GraphicsDriver::instance->present();

	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

	std::chrono::milliseconds milliSec =
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	if (milliSec.count() < 17)
	{
		SDL_Delay(17 - milliSec.count());
	}
	else
	{
		//std::cout << milliSec.count() << std::endl;
	}
}
