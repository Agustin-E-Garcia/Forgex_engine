#include "Transform.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() {}
Transform::~Transform() {}

glm::mat4 Transform::GetModelMatrix() const { return m_ModelMatrix; }
glm::vec3 Transform::GetPosition() const { return m_Position; }
glm::vec3 Transform::GetRotation() const { return m_Rotation; }
glm::vec3 Transform::GetScale() const { return m_Scale; }

glm::vec3 Transform::GetForward() const { return m_Forward; }
glm::vec3 Transform::GetRight() const { return m_Right; }
glm::vec3 Transform::GetUp() const { return m_Up; }

void Transform::SetPosition(glm::vec3 newPosition)
{
	m_Position = newPosition;
	m_LocationMatrix = glm::translate(glm::mat4(1.0f), newPosition);
	UpdateModelMatrix();
}

void Transform::SetRotationX(float amount)
{
	m_Rotation.x = glm::clamp(amount, -glm::pi<float>() / 2.0f, glm::pi<float>() / 2.0f); // Limit pitch to prevent flipping
	UpdateRotation();
}

void Transform::SetRotationY(float amount)
{
	m_Rotation.y = amount;
	UpdateRotation();
}

void Transform::SetRotationZ(float amount)
{
	m_Rotation.z = amount;
	UpdateRotation();
}

void Transform::UpdateRotation() 
{
	glm::quat qX = glm::angleAxis(m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat qY = glm::angleAxis(m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat qZ = glm::angleAxis(m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	m_RotationQuat = qZ * qY * qX;

	m_RotationMatrix = glm::mat4_cast(m_RotationQuat);

	UpdateVectors();
	UpdateModelMatrix();
}

void Transform::SetScale(glm::vec3 newScale)
{
	m_Scale = newScale;
	m_ScaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);
	UpdateModelMatrix();
}

void Transform::UpdateVectors()
{
	m_Forward = glm::vec3(m_RotationMatrix[2]);
	m_Up = glm::vec3(m_RotationMatrix[1]);
	m_Right = glm::vec3(m_RotationMatrix[0]);
}

void Transform::UpdateModelMatrix()
{
	m_ModelMatrix = m_LocationMatrix * m_RotationMatrix * m_ScaleMatrix;
}