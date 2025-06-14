#pragma once
#include "CoreExports.h"
#include "Layer/LayerStack.h"
#include "InputManager.h"
#include "SessionContext.h"

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
	protected:
		LayerStack m_LayerStack;
	private:
		bool m_ShouldClose;
		InputManager m_InputManager;
		SessionContext m_SessionContext;	

		Graphics::Window* m_Window;
	};
}
