#pragma once
#include "Object.h"

class ENGINE_API Camera : public Object
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f));
	Camera(glm::vec3 position, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	~Camera();

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

private:
	float m_AspectRatio;
	float m_FieldOfView;
	float m_NearPlane;
	float m_FarPlane;
};