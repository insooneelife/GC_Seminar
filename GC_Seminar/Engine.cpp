#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsDriver.h"
#include "EntityManager.h"
#include "World.h"
#include "Camera2D.h"
#include "UIManager.h"
#include "Utils.h"
#include "Network/Network/NetworkManagerClient.h"

#include "Entity/Hunter.h"

Engine::Engine()
	:
	_world(nullptr)
{}

Engine::~Engine()
{}

void Engine::handleEvent(SDL_Event* ev)
{
	handleEventInLobby(ev);
	handleEventInRoom(ev);
	handleEventInGame(ev);
}

void Engine::handleEventInLobby(SDL_Event* ev)
{
	switch (ev->type)
	{
	case SDL_KEYDOWN:
		// Details
		NetworkManagerClient::instance->processInput(ev->key.keysym.sym);
		
		break;
	}
}

void Engine::handleEventInRoom(SDL_Event* ev)
{
}

void Engine::handleEventInGame(SDL_Event* ev)
{
	if (_world == nullptr)
		return;

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

	switch (ev->type)
	{
	case SDL_KEYDOWN:
		// Details
		switch (ev->key.keysym.sym)
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
		switch (ev->key.keysym.sym)
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

		//button = UIManager::instance->trySelect(Vec2(mx, my));
		//if(button)
		//button->update();

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
		break;
	case SDL_MOUSEWHEEL:
		if (ev->wheel.y > 0)
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

bool Engine::init(const std::string& server_addr, const std::string& client_name)
{
	NetworkManagerClient::staticInit(server_addr, client_name);

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

	return true;
}

void Engine::initWorld()
{
	_world.reset(new World(2400, 1400));

	UIManager::staticInit();
	UIManager::instance->addButton(new Button(*_world, _world->genID(), Vec2(80, 70), "Damage"));
	UIManager::instance->addButton(new Button(*_world, _world->genID(), Vec2(180, 70), "Range"));
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
	// World의 update
	if(_world)
		_world->update();
	
	NetworkManagerClient::instance->update();

	// 새 그래픽 버퍼를 준비한다.
	GraphicsDriver::instance->clear();
	
	// 화면에 그려질 모든 객체들을 그린다.
	if (_world)
		_world->render();
	GraphicsDriver::instance->render();
	//UIManager::instance->render();

	// 그래픽 버퍼를 화면에 출력한다.
	GraphicsDriver::instance->present();
}
