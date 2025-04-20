#pragma once
#include "CoreExports.h"
#include "Layer/LayerStack.h"

namespace Forgex::Graphics{ class Window; }

class CORE_API Application
{
public:
	Application();
	~Application();

	void InitializeSystems();
	void Run();
private:
	bool m_ShouldClose;
	LayerStack m_LayerStack;

	Forgex::Graphics::Window* m_Window;
};