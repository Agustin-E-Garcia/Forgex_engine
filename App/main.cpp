#include "Engine.h"

int main()
{
	Engine* engine = new Engine();
	if (engine->Start()) 
	{
		engine->Loop();
	}
	engine->Quit();

	delete engine;
	std::cin.get();

	return 0;
}