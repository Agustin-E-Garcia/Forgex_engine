#include "InputManager.h"
#include "Layer/LayerStack.h"
#include <ForgexGraphics.h>

namespace Forgex::Core
{
	InputManager::InputManager() {}
	InputManager::~InputManager() {}

	void InputManager::SetWindow(Graphics::Window* ActiveWindow)
	{
		m_ActiveWindow = ActiveWindow;
		// Register to window events
		m_ActiveWindow->RegisterWindowResizeCallback([this](unsigned int w, unsigned int h) { m_EventQueue.push(new WindowResizedEvent(w, h)); });
		m_ActiveWindow->RegisterKeyPressedCallback([this](unsigned int keycode, bool repeat, bool pressed) { m_EventQueue.push(new KeyPressedEvent(keycode, repeat, pressed)); });
		m_ActiveWindow->RegisterMouseMoveCallback([this](double xPos, double yPos) { m_EventQueue.push(new MousePositionEvent(xPos, yPos)); });
		m_ActiveWindow->RegisterMouseClickedCallback([this](unsigned int button, bool pressed) { m_EventQueue.push(new MouseClickEvent(button, pressed)); });
	}

	void InputManager::ConsumeEvents(LayerStack& layerStack)
	{
		while (!m_EventQueue.empty())
		{
			for (auto it = layerStack.end(); it != layerStack.begin();)
			{
				if (m_EventQueue.empty()) return;

				Event* next = m_EventQueue.front();

				(*--it)->OnEvent(next);
				if (next->m_Handled) 
				{
					m_EventQueue.pop();
					delete next;
				}
			}
		}
	}
}