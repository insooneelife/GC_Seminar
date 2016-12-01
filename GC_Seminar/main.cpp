#include "Windows.h"
#include "WindowManager.h"
#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include "Engine.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	AllocConsole();
	FILE* file = new FILE();
	freopen_s(&file, "CONOUT$", "w", stdout);

	if (__argc != 3)
	{
		std::cout << "argument example : 127.0.0.1:8000 insooneelife" << std::endl;
		return 1;
	}

	Engine engine;
	if (engine.init(__argv[1], __argv[2]))
	//if(engine.init("127.0.0.1:8000", "insooneelife"))
	{
		return engine.run();
	}
	else
	{
		return 1;
	}
	
}