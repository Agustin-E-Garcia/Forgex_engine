#include "CameraComponent.h"
#include "TransformComponent.h"
#include "../Object.h"
#include <ForgexMath.h>

namespace Forgex::Scene
{
	CameraComponent::CameraComponent() : Component("Camera")
	{
		m_FieldOfView = 90.0f;
		m_AspectRatio = {4,3};
		m_NearPlane = 0.1f;
		m_FarPlane = 1000.0f;
	}
	
	CameraComponent::~CameraComponent() {}
	
	Math::Mat4 CameraComponent::GetProjectionMatrix() const
	{
		return Math::Perspective(Math::Radians(m_FieldOfView), (m_AspectRatio.x / m_AspectRatio.y), m_NearPlane, m_FarPlane);
	}
	
	Math::Mat4 CameraComponent::GetViewMatrix() const
	{
		return Math::LookAt(m_ObjectTransform->GetPosition(),
							m_ObjectTransform->GetPosition() + m_ObjectTransform->GetForward(),
							Math::Vec3(0, 1, 0));
	}

	void CameraComponent::OnAttach()
	{
		m_ObjectTransform = m_Owner->GetTransform();
		m_ObjectTransform->SetPosition(Math::Vec3(0.0f, 0.0f, -2.0f));
	}
}
