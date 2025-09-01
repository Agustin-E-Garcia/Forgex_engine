#include "TransformComponent.h"

namespace Forgex::Scene
{
	TransformComponent::TransformComponent() : Component("Transform") {}
	TransformComponent::~TransformComponent() = default;

	Math::Mat4 TransformComponent::GetModelMatrix() const { return m_ModelMatrix; }
	Math::Vec3 TransformComponent::GetPosition() const { return m_Position; }
	Math::Vec3 TransformComponent::GetRotation() const { return m_Rotation; }
	Math::Vec3 TransformComponent::GetScale() const { return m_Scale; }

	Math::Vec3 TransformComponent::GetForward() const { return m_Forward; }
	Math::Vec3 TransformComponent::GetRight() const { return m_Right; }
	Math::Vec3 TransformComponent::GetUp() const { return m_Up; }

    void TransformComponent::Update(float deltaTime)
    {
        UpdateRotation();
    }

	void TransformComponent::SetPosition(Math::Vec3 newPosition)
	{
		m_Position = newPosition;
		m_LocationMatrix = Math::Translate(Math::Mat4(1.0f), newPosition);
		UpdateModelMatrix();
	}

	void TransformComponent::SetRotationX(float amount)
	{
		// Limit pitch to prevent flipping
		m_Rotation.x = Math::Clamp(amount, -Math::Pi() / 2.0f, Math::Pi() / 2.0f);
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
		Math::Quat qX = Math::AngleAxis(m_Rotation.x, Math::Vec3(1.0f, 0.0f, 0.0f));
		Math::Quat qY = Math::AngleAxis(m_Rotation.y, Math::Vec3(0.0f, 1.0f, 0.0f));
		Math::Quat qZ = Math::AngleAxis(m_Rotation.z, Math::Vec3(0.0f, 0.0f, 1.0f));

		m_RotationQuat = qZ * qY * qX;

		m_RotationMatrix = Mat4_Cast(m_RotationQuat);

		UpdateVectors();
		UpdateModelMatrix();
	}

	void TransformComponent::SetScale(Math::Vec3 newScale)
	{
		m_Scale = newScale;
		m_ScaleMatrix = Scale(Math::Mat4(1.0f), m_Scale);
		UpdateModelMatrix();
	}

	void TransformComponent::UpdateVectors()
	{
		m_Forward = Math::Vec3(m_RotationMatrix[2]);
		m_Up = Math::Vec3(m_RotationMatrix[1]);
		m_Right = Math::Vec3(m_RotationMatrix[0]);
	}

	void TransformComponent::UpdateModelMatrix()
	{
		m_ModelMatrix = m_LocationMatrix * m_RotationMatrix * m_ScaleMatrix;
	}
}
