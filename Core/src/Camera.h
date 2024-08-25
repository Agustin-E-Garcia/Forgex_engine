#pragma once
#include "Entity.h"

class ENGINE_API Camera : public Entity
{
public:
	Camera();
	Camera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	~Camera();

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

private:
	float m_AspectRatio;
	float m_FieldOfView;
	float m_NearPlane;
	float m_FarPlane;
};