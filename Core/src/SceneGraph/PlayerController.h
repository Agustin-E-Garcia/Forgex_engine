#pragma once
#include "Component.h"
#include "Transform.h"
#include "ComponentRegistry.h"
#include "../InputManager.h"

class ENGINE_API PlayerController : public Component
{
public:
	PlayerController() : Component("Player Controller") { };
	~PlayerController() {};

protected:
	void DrawCustomEditor() override 
	{
		ImGui::InputFloat3("Speed", &m_Speed.x);
	}

	void OnUpdate(float deltaTime) override
	{
		if (!m_Transform) m_Transform = m_Owner->GetTransform();

		m_Speed = glm::vec3(0);

		if (InputManager::IsKeyPressed(65))		m_Speed.x = 10.0;
		if (InputManager::IsKeyPressed(68))		m_Speed.x = -10.0;
		if (InputManager::IsKeyPressed(87))		m_Speed.z = 20.0;
		if (InputManager::IsKeyPressed(83))		m_Speed.z = -20.0;
		if (InputManager::IsKeyPressed(340))	m_Speed.y = -20.0;
		if (InputManager::IsKeyPressed(32))		m_Speed.y = 20.0;

		m_Transform->SetPosition(m_Transform->GetPosition() + m_Transform->GetForward() * m_Speed.z * deltaTime);
		m_Transform->SetPosition(m_Transform->GetPosition() + m_Transform->GetUp() * m_Speed.y * deltaTime);
		m_Transform->SetRotationY(m_Transform->GetRotation().y + m_Speed.x * deltaTime);
	}

private:
	glm::vec3 m_Speed = glm::vec3(0);
	Transform* m_Transform = nullptr;
};

REGISTER_COMPONENT(PlayerController)