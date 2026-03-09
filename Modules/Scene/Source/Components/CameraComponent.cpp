#include "CameraComponent.h"
#include "TransformComponent.h"
#include "../Object.h"

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
	
	glm::mat4 CameraComponent::GetProjectionMatrix() const
	{
		return glm::perspective(glm::radians(m_FieldOfView), (m_AspectRatio.x / m_AspectRatio.y), m_NearPlane, m_FarPlane);
	}
	
	glm::mat4 CameraComponent::GetViewMatrix() const
	{
		return glm::lookAt(m_ObjectTransform->GetPosition(),
							m_ObjectTransform->GetPosition() + m_ObjectTransform->GetForward(),
							glm::vec3(0, 1, 0));
	}

	void CameraComponent::OnAttach()
	{
		m_ObjectTransform = m_Owner->GetTransform();
		m_ObjectTransform->SetPosition(glm::vec3(0.0f, 0.0f, -2.0f));
	}
}
