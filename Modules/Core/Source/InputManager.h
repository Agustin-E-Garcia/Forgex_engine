#pragma once
#include "CoreExports.h"
#include "Event/EventList.h"
#include <queue>

namespace Forgex::Graphics { class Window; }

namespace Forgex::Core
{
	class LayerStack;

	class CORE_API InputManager
	{
	public:
		InputManager();
		~InputManager();

		void SetWindow(Graphics::Window* ActiveWindow);
		void ConsumeEvents(LayerStack& layerStack);

	private:
		std::queue<Event*> m_EventQueue;
		Graphics::Window* m_ActiveWindow;
	};
}