#pragma once
#include "Transform.h"
#include "Log.h"
#include <imgui/imgui.h>

class ENGINE_API Object 
{
public:
	Object(const char* name) : m_Name(name), m_UniqueIdentifier(std::rand()) { LOG_CORE_TRACE("Object created - Name: {0} - UID: {1} ", name, m_UniqueIdentifier); };
	~Object() {};

	inline Transform* GetTransform() { return &m_Transform; }
	inline uint32_t GetUID() { return m_UniqueIdentifier; }

	inline void ChangeName(const char* newName) { m_Name = newName; }

	void DrawEditor() { DrawCustomEditor(); }
	virtual void DrawCustomEditor() {};

private:
	const char* m_Name;
	uint32_t m_UniqueIdentifier;
	
	Transform m_Transform;
};