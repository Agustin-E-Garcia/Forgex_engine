#pragma once
#include "Exports.h"

class Window;
class Renderer;

class ENGINE_API Application 
{
public:
	Application();
	~Application();

	void InitializeSystems();
	void Run();

private:
	Window* m_Window;
	Renderer* m_Renderer;
};