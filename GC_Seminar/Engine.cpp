#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsDriver.h"
#include "EntityManager.h"
#include "World.h"
#include "Camera2D.h"
#include "Utils.h"

#include "Entity/Snake.h"

Engine::Engine()
{}

Engine::~Engine()
{}

void Engine::handleEvent(SDL_Event* inEvent)
{
	Snake* player = _world->getPlayerEntity();
	Vec2 heading;

	static bool press[255] = { 0 };
	const float distance = 100;
	const Vec2 left(-1, 0);
	const Vec2 right(1, 0);
	const Vec2 up(0, 1);
	const Vec2 down(0, -1);

	int mx = 0;
	int my = 0;

	switch (inEvent->type)
	{
	case SDL_KEYDOWN:
		// Details
		if (player)
		{
			switch (inEvent->key.keysym.sym)
			{
			case SDLK_a:
					player->setHeading(left);
				break;

			case SDLK_d:
					player->setHeading(right);
				break;

			case SDLK_w:
					player->setHeading(up);
				break;

			case SDLK_s:
					player->setHeading(down);
				break;

			case SDLK_SPACE:
				break;

			default:
				break;
			}
		}
		break;

	case SDL_KEYUP:
		break;

	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&mx, &my);
		
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mx, &my);
		break;
	case SDL_MOUSEWHEEL:
		if (inEvent->wheel.y > 0)
		{
			Camera2D::instance->setScale(
				Camera2D::instance->getScale() + Vec2(0.1f, 0.1f));
		}
		else
		{
			Vec2 scale = Camera2D::instance->getScale();
			Camera2D::instance->setScale(scale - Vec2(0.1f, 0.1f));
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

	_world.reset(new World(30000));

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


#include <chrono>
void Engine::update()
{
	std::chrono::duration<double> start = std::chrono::system_clock::now().time_since_epoch();
	// World의 update
	_world->update();

	std::chrono::duration<double> end = std::chrono::system_clock::now().time_since_epoch();
	
	// 새 그래픽 버퍼를 준비한다.
	GraphicsDriver::instance->clear();
	
	// 화면에 그려질 모든 객체들을 그린다.
	_world->render();
	GraphicsDriver::instance->render();

	// 그래픽 버퍼를 화면에 출력한다.
	GraphicsDriver::instance->present();

	std::chrono::duration<double> end2 = std::chrono::system_clock::now().time_since_epoch();
	std::cout <<"u : "<< (end - start).count()<<"  r : "<< (end2 - end).count() << std::endl;
}
