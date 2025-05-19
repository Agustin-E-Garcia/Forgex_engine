#pragma once
#include "CoreExports.h"
#include "Layer/LayerStack.h"
#include "InputManager.h"

namespace Forgex::Graphics { class Window; }

namespace Forgex::Core
{
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
		InputManager m_InputManager;

		Graphics::Window* m_Window;
	};
}