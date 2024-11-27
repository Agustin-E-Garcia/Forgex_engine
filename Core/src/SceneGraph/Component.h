#pragma once
#include "../Exports.h"
#include "../Renderer.h"
#include "../Profiler/Profiler.h"
#include <imgui/imgui.h>
#include <functional>

class Object;

class ENGINE_API Component
{
public:
	Component(const char* name) : m_Name(name) {}
	~Component() {}

	void DrawEditor()
	{
		ImGui::SeparatorText(m_Name);
		DrawCustomEditor();
		ImGui::Separator();
	}

	void Update(float deltaTime) 
	{
		OnUpdate(deltaTime);
	}

	virtual void Render(const Renderer& renderer) {}

	inline const char* GetName() { return m_Name; }
	inline Object* GetOwner() { return m_Owner; }
	inline void SetParent(Object* parent) { m_Owner = parent; }

protected:
	const char* m_Name;
	Object* m_Owner = nullptr;

	virtual void DrawCustomEditor() {};
	virtual void OnUpdate(float deltaTime) {}
};