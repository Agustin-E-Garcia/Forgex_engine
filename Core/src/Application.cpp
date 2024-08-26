#include "Application.h"
#include "Log.h"
#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include "Chunk.h"
#include "InputDetector.h"
#include "GLFW/glfw3.h"

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
	InputDetector::Init();
	m_Renderer = new Renderer();
}

void Application::Run()
{
	Camera camera;
	Chunk chunk;

	camera.SetPosition(glm::vec3(0.0f, 10.0f, -25.0f));
	m_Renderer->SetActiveCamera(&camera);

	glm::vec3 speed(0.0f);

	float lastTime = glfwGetTime();

	do
	{
		// Delta time calculation
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Camera Controls
		{
			if (IS_KEY_PRESSED(KEY_W))			 speed.z += 10.0f * deltaTime;
			if (IS_KEY_PRESSED(KEY_S))			 speed.z -= 10.0f * deltaTime;
			if (IS_KEY_PRESSED(KEY_A))			 speed.x += 10.0f * deltaTime;
			if (IS_KEY_PRESSED(KEY_D))			 speed.x -= 10.0f * deltaTime;
			if (IS_KEY_PRESSED(KEY_SPACE))		 speed.y += 10.0f * deltaTime;
			if (IS_KEY_PRESSED(KEY_LEFT_SHIFT))  speed.y -= 10.0f * deltaTime;

			camera.SetPosition(camera.GetPosition() + (camera.GetForward() * speed.z) + (camera.GetUp() * speed.y));
			camera.SetRotationY(camera.GetRotation().y + speed.x);

			speed = glm::vec3(0.0f);
		}
		
		m_Renderer->ClearScreen();
		m_Renderer->DrawVoxel(chunk.GetDrawInfo());
		m_Window->Update();
	} while (!m_Window->ShouldClose() && !IS_KEY_PRESSED(GLFW_KEY_ESCAPE));
}