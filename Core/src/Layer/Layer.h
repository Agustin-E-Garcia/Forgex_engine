#pragma once
#include "../Exports.h"
#include "../Event/EventList.h"
#include "../Renderer.h"

class ENGINE_API Layer 
{
	using EventCallbackFn = std::function<void(Event&)>;

public:
	Layer(const char* name) : m_Name(name) {}
	Layer(const char* name, const EventCallbackFn& callback) : m_Name(name), m_EventCallback(callback) {}
	virtual ~Layer() {}

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnEvent(Event& event) {}
	virtual void OnRender(const Renderer& renderer) {}

	inline const char* GetName() const { return m_Name; }
	inline void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; };

protected:
	EventCallbackFn m_EventCallback;

private:
	const char* m_Name;
};