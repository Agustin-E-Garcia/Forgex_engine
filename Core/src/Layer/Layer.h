#pragma once
#include "../Exports.h"
#include "../Event/EventList.h"

class ENGINE_API Layer 
{
public:
	Layer(const char* name) : m_Name(name) {}
	virtual ~Layer() {}

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnEvent(Event& event) {}
	virtual void OnRender() {}

	inline const char* GetName() const { return m_Name; }

private:
	const char* m_Name;
};