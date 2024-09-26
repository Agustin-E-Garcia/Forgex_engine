#pragma once
#include "Exports.h"
#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"

class ENGINE_API Transform
{
public:
	Transform();
	~Transform();

	glm::mat4 GetModelMatrix() const;

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	glm::vec3 GetForward() const;
	glm::vec3 GetRight() const;
	glm::vec3 GetUp() const;

	void SetPosition(glm::vec3 newPosition);
	void SetRotationX(float amount);
	void SetRotationY(float amount);
	void SetRotationZ(float amount);
	void SetScale(glm::vec3 newScale);

private:
	glm::vec3 m_Position = glm::vec3(0.0f);
	glm::vec3 m_Rotation = glm::vec3(0.0f);
	glm::vec3 m_Scale = glm::vec3(1.0f);

	glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::quat m_RotationQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
	glm::mat4 m_LocationMatrix = glm::mat4(1.0f);
	glm::mat4 m_ScaleMatrix = glm::mat4(1.0f);
	glm::mat4 m_RotationMatrix = glm::mat4(1.0f);

	void UpdateModelMatrix();
	void UpdateVectors();
	void UpdateRotation();
};