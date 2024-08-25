#include "Application.h"
#include "Log.h"
#include "Window.h"
#include "Renderer.h"
#include "Cube.h"
#include "Camera.h"

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
	Camera camera;
	Cube cube;

	camera.SetPosition(glm::vec3(0.0f, 2.0f, -10.0f));
	cube.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_Renderer->SetActiveCamera(&camera);

	do
	{
		m_Renderer->ClearScreen();
		m_Renderer->Draw(cube.GetDrawInfo());
		m_Window->Update();
	} while (!m_Window->ShouldClose());
}