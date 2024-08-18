#include "EngineInstance.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

bool EngineInstance::Start()
{
	if (!glewInit()) return false;
	if (!glfwInit()) return false;

	glm::vec3 vector = { 0.0f, 0.0f, 0.0f };

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