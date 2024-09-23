#pragma once
#include "Transform.h"
#include <imgui/imgui.h>

class ENGINE_API Object 
{
public:
	Object(const char* name) : m_Name(name), m_UniqueIdentifier(std::rand()) {};
	~Object() {};

	Transform* GetTransform() { return &m_Transform; }

	void DrawEditor() { DrawCustomEditor(); }
	virtual void DrawCustomEditor() {};

private:
	const char* m_Name;
	uint32_t m_UniqueIdentifier;
	
	Transform m_Transform;
};