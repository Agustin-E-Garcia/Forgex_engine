#include "Camera.h"
#include "Transform.h"
#include "Object.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../Log.h"
#include "../Application.h"

Camera::Camera() : Component("Camera")
{
	m_FieldOfView = 90.0f;
	m_AspectRatio = glm::vec2(4, 3);
	m_NearPlane = 0.1f;
	m_FarPlane = 1000.0f;
}

Camera::Camera(int fieldOfView, glm::vec2 aspectRatio, float nearPlane, float farPlane) : Component("Camera")
{
	m_FieldOfView = fieldOfView;
	m_AspectRatio = aspectRatio;
	m_NearPlane = nearPlane;
	m_FarPlane = farPlane;
}

Camera::~Camera() {}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians((float)m_FieldOfView), (m_AspectRatio.x / m_AspectRatio.y), m_NearPlane, m_FarPlane);
}

glm::mat4 Camera::GetViewMatrix()
{
	if (!m_ObjectTransform) 
	{
		m_ObjectTransform = m_Owner->GetTransform();
	}

	return glm::lookAt(m_ObjectTransform->GetPosition(), m_ObjectTransform->GetPosition() + m_ObjectTransform->GetForward(), glm::vec3(0, 1, 0));
}

void Camera::DrawCustomEditor()
{
	ImGui::BeginDisabled(m_IsActiveCamera);
	if (ImGui::Checkbox("Active Camera", &m_IsActiveCamera)) 
	{
		Application::SetActiveCamera(this);
	}
	ImGui::EndDisabled();
	ImGui::SliderInt("Field of View", &m_FieldOfView, 80, 120);
	ImGui::InputFloat2("Aspect Ratio", &m_AspectRatio.x);
	ImGui::InputFloat("Near plane", &m_NearPlane);
	ImGui::InputFloat("Far plane", &m_FarPlane);
}