#pragma once
#include "Exports.h"
#include <vector>
#include <optional>
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

	void SetPosition(glm::vec3 newPosition);
	void SetRotationX(float amount);
	void SetRotationY(float amount);
	void SetRotationZ(float amount);
	void SetScale(glm::vec3 newScale);

	DrawInfo GetDrawInfo();

protected:
	std::vector<float> m_Vertices;
	std::vector<float> m_UVs;
	std::vector<unsigned int> m_Indices;

	unsigned int m_VertexBufferID = 0;

	void GenerateVertexBuffer();

private:
	glm::vec3 m_Position = glm::vec3(1.0f);
	glm::vec3 m_Rotation = glm::vec3(1.0f);
	glm::vec3 m_Scale = glm::vec3(1.0f);

	glm::mat4 m_LocationMatrix = glm::mat4(1.0f);
	glm::mat4 m_RotationMatrix = glm::mat4(1.0f);
	glm::mat4 m_ScaleMatrix = glm::mat4(1.0f);
	glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

	void UpdateModelMatrix();
};