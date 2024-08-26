#include "InputDetector.h"
#include "GLFW/glfw3.h"
#include "Log.h"

void InputDetector::Init()
{
	GLFWwindow* window = glfwGetCurrentContext();

	if (window == nullptr) 
	{
		LOG_CORE_ERROR("Input detector could not be initialized as there is no current context available");
		return;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	LOG_CORE_INFO("Input detector intialized for window '{0}'", glfwGetWindowTitle(window));
}

bool InputDetector::IsKeyPressed(int key)
{
	return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
}