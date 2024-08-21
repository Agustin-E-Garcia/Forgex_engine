#pragma once
#include "Exports.h"

class GLFWwindow;

class ENGINE_API Window
{
public:
	Window(int width, int height, char* title);
	~Window();

	void Update();
	bool ShouldClose();

private:
	GLFWwindow* m_Window;
};