#include "Application.h"
#include "Log.h"
#include "Window.h"
#include "Renderer.h"
#include "Cube.h"

Application::Application() 
{
	InitializeSystems();
}

Application::~Application() 
{
	delete m_Renderer;
	delete m_Window;
}

void Application::InitializeSystems()
{
	Log::Init();
	m_Window = new Window(800, 600, "Voxel_Engine");
	m_Renderer = new Renderer();
}

void Application::Run()
{
	Cube cube;

	do
	{
		m_Renderer->ClearScreen();
		m_Renderer->Draw(cube.GetDrawInfo());
		m_Window->Update();
	} while (!m_Window->ShouldClose());
}