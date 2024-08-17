#include "EngineInstance.h"

bool EngineInstance::Start()
{
	return OnStart();
}

bool EngineInstance::Quit()
{
	OnQuit();
	return true;
}

void EngineInstance::Loop()
{
	do 
	{
		m_Quit = OnLoop();
	} while (!m_Quit);
}