#pragma once
#include "../CoreExports.h"
#include "../Event/EventList.h"
#include <string>

namespace Forgex::Graphics::Resources { struct Framebuffer; }

namespace Forgex::Core
{
	class CORE_API Layer
	{
		using EventCallbackFn = std::function<void(Event&)>;

	public:
		Layer(std::string name) : m_Name(name) {}
		Layer(std::string name, const EventCallbackFn& callback) : m_EventCallback(callback), m_Name(name) {}
		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnBegin() = 0;
		virtual void OnEnd() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
		virtual void OnEvent(Event* event) = 0;
		virtual void OnRender(const Graphics::Resources::Framebuffer* framebufferID) = 0;

		std::string GetName() const { return m_Name; }
		void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }

	protected:
		EventCallbackFn m_EventCallback;

	private:
		std::string m_Name;
	};
}
