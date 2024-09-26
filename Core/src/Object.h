#pragma once
#include "Transform.h"
#include "Log.h"
#include "Renderer.h"
#include <imgui/imgui.h>

class ENGINE_API Object 
{
public:
	Object(const char* name) : m_Name(name), m_UniqueIdentifier(std::rand()) { LOG_CORE_TRACE("Object created - Name: {0} - UID: {1} ", name, m_UniqueIdentifier); };
	~Object() {};

	inline const Transform* GetTransform() const { return &m_Transform; }
	inline Transform* GetTransformUnsafe() { return &m_Transform; }
	inline uint32_t GetUID() { return m_UniqueIdentifier; }
	inline const char* GetName() { return m_Name; }

	inline void ChangeName(const char* newName) { m_Name = newName; }

	void DrawEditor() { DrawCustomEditor(); }
	virtual void DrawCustomEditor() {};
	virtual void Update(float deltaTime) {};
	virtual void Render(const Renderer& renderer) {};

private:
	const char* m_Name;
	uint32_t m_UniqueIdentifier;
	
	Transform m_Transform;
};