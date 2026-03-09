#include "TransformComponent.h"
#include "glm/ext/matrix_transform.hpp"

namespace Forgex::Scene
{
	TransformComponent::TransformComponent() : Component("Transform") {}
	TransformComponent::~TransformComponent() = default;

	glm::mat4 TransformComponent::GetModelMatrix() const { return m_ModelMatrix; }
	glm::vec3 TransformComponent::GetPosition() const { return m_Position; }
	glm::vec3 TransformComponent::GetRotation() const { return m_Rotation; }
	glm::vec3 TransformComponent::GetScale() const { return m_Scale; }

	glm::vec3 TransformComponent::GetForward() const { return m_Forward; }
	glm::vec3 TransformComponent::GetRight() const { return m_Right; }
	glm::vec3 TransformComponent::GetUp() const { return m_Up; }

    void TransformComponent::Update(float deltaTime)
    {
        UpdateRotation();
    }

	void TransformComponent::SetPosition(glm::vec3 newPosition)
	{
		m_Position = newPosition;
		m_LocationMatrix = glm::translate(glm::mat4(1.0f), newPosition);
		UpdateModelMatrix();
	}

	void TransformComponent::SetRotationX(float amount)
	{
		// Limit pitch to prevent flipping
		m_Rotation.x = glm::clamp(amount, -glm::pi<float>() / 2.0f, glm::pi<float>() / 2.0f);
		UpdateRotation();
	}

	void TransformComponent::SetRotationY(float amount)
	{
		m_Rotation.y = amount;
		UpdateRotation();
	}

	void TransformComponent::SetRotationZ(float amount)
	{
		m_Rotation.z = amount;
		UpdateRotation();
	}

	void TransformComponent::UpdateRotation() 
	{
		glm::quat qX = glm::angleAxis(m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat qY = glm::angleAxis(m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat qZ = glm::angleAxis(m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		m_RotationQuat = qZ * qY * qX;

		m_RotationMatrix = glm::mat4_cast(m_RotationQuat);

		UpdateVectors();
		UpdateModelMatrix();
	}

	void TransformComponent::SetScale(glm::vec3 newScale)
	{
		m_Scale = newScale;
		m_ScaleMatrix =  glm::scale(glm::mat4(1.0f), m_Scale);
		UpdateModelMatrix();
	}

	void TransformComponent::UpdateVectors()
	{
		m_Forward = glm::vec3(m_RotationMatrix[2]);
		m_Up = glm::vec3(m_RotationMatrix[1]);
		m_Right = glm::vec3(m_RotationMatrix[0]);
	}

	void TransformComponent::UpdateModelMatrix()
	{
		m_ModelMatrix = m_LocationMatrix * m_RotationMatrix * m_ScaleMatrix;
	}
}
