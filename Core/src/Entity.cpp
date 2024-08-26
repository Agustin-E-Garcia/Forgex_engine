#include "Entity.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

Entity::Entity() {}
Entity::~Entity() {}

glm::mat4 Entity::GetModelMatrix() { return m_ModelMatrix; }
glm::vec3 Entity::GetPosition() { return m_Position; }
glm::vec3 Entity::GetRotation() { return m_Rotation; }
glm::vec3 Entity::GetScale() { return m_Scale; }

glm::vec3 Entity::GetForward() { return m_Forward; }
glm::vec3 Entity::GetRight() { return m_Right; }
glm::vec3 Entity::GetUp() { return m_Up; }

void Entity::SetPosition(glm::vec3 newPosition)
{
	m_Position = newPosition;
	m_LocationMatrix = glm::translate(glm::mat4(1.0f), newPosition);
	UpdateModelMatrix();
}

void Entity::SetRotationX(float amount)
{
	m_Rotation[0] = amount;
	m_RotationMatrix = glm::rotate(glm::mat4(1.0f), amount, glm::vec3(1.0f, 0.0f, 0.0f));

	m_Forward = glm::vec3(m_RotationMatrix[2]);
	m_Up = glm::vec3(m_RotationMatrix[1]);

	UpdateModelMatrix();
}

void Entity::SetRotationY(float amount)
{
	m_Rotation[1] = amount;
	m_RotationMatrix = glm::rotate(glm::mat4(1.0f), amount, glm::vec3(0.0f, 1.0f, 0.0f));

	m_Forward = glm::vec3(m_RotationMatrix[2]);
	m_Right = glm::vec3(m_RotationMatrix[0]);
	
	UpdateModelMatrix();
}

void Entity::SetRotationZ(float amount)
{
	m_Rotation[2] = amount;
	m_RotationMatrix = glm::rotate(glm::mat4(1.0f), amount, glm::vec3(0.0f, 0.0f, 1.0f));
	
	m_Right = glm::vec3(m_RotationMatrix[0]);
	m_Up = glm::vec3(m_RotationMatrix[1]);

	UpdateModelMatrix();
}

void Entity::SetScale(glm::vec3 newScale)
{
	m_Scale = newScale;
	m_ScaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);
	UpdateModelMatrix();
}

void Entity::UpdateModelMatrix()
{
	m_ModelMatrix = m_LocationMatrix * m_RotationMatrix * m_ScaleMatrix;
}