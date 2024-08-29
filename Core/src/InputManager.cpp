#include "InputManager.h"
#include "GLFW/glfw3.h"
#include "Log.h"

InputManager* InputManager::s_Instance = nullptr;

InputManager::InputManager() 
{
	GLFWwindow* window = glfwGetCurrentContext();

	if (window == nullptr)
	{
		LOG_CORE_ERROR("Input detector could not be initialized as there is no current context available");
		return;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	int w, h;
	glfwGetWindowSize(window, &w, &h);

	offsetX = 0;
	offsetY = 0;
	lastXPosition = w / 2;
	lastYPosition = h / 2;

	LOG_CORE_INFO("Input detector intialized for window '{0}'", glfwGetWindowTitle(window));
};

InputManager::~InputManager() {}

void InputManager::UpdateImp()
{
	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);

	offsetX = (x - lastXPosition) * -1;
	offsetY = (lastYPosition - y) * -1;

	lastXPosition = x;
	lastYPosition = y;

	const float sensitivity = 0.1f;
	offsetX *= sensitivity;
	offsetY *= sensitivity;
}

bool InputManager::IsKeyPressed(int key)
{
	return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
}

void InputManager::GetMouseInput(float* x, float* y)
{
	if (s_Instance == nullptr) 
	{
		LOG_CORE_ERROR("No input manager initialized, make sure to initialize once before any calls to GetMouseInput()");
		return;
	}

	*x = s_Instance->offsetX;
	*y = s_Instance->offsetY;
}



//void InputDetector::Mouse_Callback(GLFWwindow* window, double xPos, double yPos)
//{
//	float xOffset = xPos - s_LastMousePosition.x;
//	float yOffset = s_LastMousePosition.y - yPos;
//	s_LastMousePosition = glm::vec2(xPos, yPos);
//
//	const float sensitivity = 0.1f;
//	xOffset *= sensitivity;
//	yOffset *= sensitivity;
//
//	s_MouseDelta = glm::vec2(xOffset, yOffset);
//}