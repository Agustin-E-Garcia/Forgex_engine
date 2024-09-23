#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Log.h"

Camera::Camera()
{
	m_FieldOfView = glm::radians(90.0f);
	m_AspectRatio = (float)4 / (float)3;
	m_NearPlane = 0.1f;
	m_FarPlane = 1000.0f;
}

Camera::Camera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	m_FieldOfView = fieldOfView;
	m_AspectRatio = aspectRatio;
	m_NearPlane = nearPlane;
	m_FarPlane = farPlane;
}

Camera::~Camera() {}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(m_FieldOfView, m_AspectRatio, m_NearPlane, m_FarPlane);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(GetPosition(), GetPosition() + GetForward(), glm::vec3(0, 1, 0));
}