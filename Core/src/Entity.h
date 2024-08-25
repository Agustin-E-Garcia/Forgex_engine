#pragma once
#include "Exports.h"
#include <glm/glm.hpp>

struct DrawInfo;

class ENGINE_API Entity
{
public:
	Entity();
	~Entity();

	glm::mat4 GetModelMatrix();

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	glm::vec3 GetForward();
	glm::vec3 GetRight();
	glm::vec3 GetUp();

	void SetPosition(glm::vec3 newPosition);
	void SetRotationX(float amount);
	void SetRotationY(float amount);
	void SetRotationZ(float amount);
	void SetScale(glm::vec3 newScale);

private:
	glm::vec3 m_Position = glm::vec3(1.0f);
	glm::vec3 m_Rotation = glm::vec3(1.0f);
	glm::vec3 m_Scale = glm::vec3(1.0f);

	glm::vec4 m_Forward = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	glm::vec4 m_Right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec4 m_Up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

	glm::mat4 m_LocationMatrix = glm::mat4(1.0f);
	glm::mat4 m_RotationMatrix = glm::mat4(1.0f);
	glm::mat4 m_ScaleMatrix = glm::mat4(1.0f);
	glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

	void UpdateModelMatrix();
};