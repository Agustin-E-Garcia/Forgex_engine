#include "Application.h"

#include "Log.h"
#include "InputManager.h"
#include "DeltaTime.h"

#include "Window.h"
#include "Renderer.h"

/* to be moved to a scene class */
/**/
#include "Camera.h"
#include "Chunk.h"
/**/

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
	DeltaTime::Init();
	m_Window = new Window(1720, 1080, "Voxel_Engine");
	InputManager::Init();
	m_Renderer = new Renderer();
}

void Application::Run()
{
	Camera camera;
	Chunk chunk;

	camera.SetPosition(glm::vec3(0.0f, 10.0f, -25.0));
	m_Renderer->SetActiveCamera(&camera);

	glm::vec3 speed(0.0f);

	do
	{

		DeltaTime::Update();
		float deltaTime = DeltaTime::GetTime();
		InputManager::Update();

		// Camera Controls
		{
			if (IS_KEY_PRESSED(KEY_W))			 speed.z += 10.0f * deltaTime;
			if (IS_KEY_PRESSED(KEY_S))			 speed.z -= 10.0f * deltaTime;
			if (IS_KEY_PRESSED(KEY_A))			 speed.x += 10.0f * deltaTime;
			if (IS_KEY_PRESSED(KEY_D))			 speed.x -= 10.0f * deltaTime;
			if (IS_KEY_PRESSED(KEY_SPACE))		 speed.y += 10.0f * deltaTime;
			if (IS_KEY_PRESSED(KEY_LEFT_SHIFT))  speed.y -= 10.0f * deltaTime;

			camera.SetPosition(camera.GetPosition() + (camera.GetRight() * speed.x) + (camera.GetForward() * speed.z) + (camera.GetUp() * speed.y));
			
			float x, y;
			InputManager::GetMouseInput(&x, &y);
			camera.SetRotationX(camera.GetRotation().x + y * 1.0 * deltaTime);
			camera.SetRotationY(camera.GetRotation().y + x * 1.0 * deltaTime);

			speed = glm::vec3(0.0f);
		}
		
		m_Renderer->ClearScreen();
		m_Renderer->DrawVoxel(chunk.GetDrawInfo());
		m_Window->Update();

	} while (!m_Window->ShouldClose() && !IS_KEY_PRESSED(GLFW_KEY_ESCAPE));
}