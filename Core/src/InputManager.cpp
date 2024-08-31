#include "InputManager.h"
#include "Application.h"
#include <GLFW/glfw3.h>

bool InputManager::IsKeyPressed(int keyCode)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetWindowPtr());
	return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

float InputManager::IsMouseButtonPressed(int button)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetWindowPtr());
	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

void InputManager::GetMousePosition(float& xPositon, float& yPosition)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetWindowPtr());
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	xPositon = (float)xpos;
	yPosition = (float)ypos;
}