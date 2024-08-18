#include "EngineInstance.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

bool EngineInstance::Start()
{
	if (!glewInit()) return false;
	if (!glfwInit()) return false;

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