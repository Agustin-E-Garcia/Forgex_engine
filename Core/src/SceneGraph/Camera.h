#pragma once
#include "Component.h"
#include "ComponentRegistry.h"

class Transform;

class ENGINE_API Camera : public Component
{
public:
	Camera();
	Camera(int fieldOfView, glm::vec2 aspectRatio, float nearPlane, float farPlane);
	~Camera();

	inline void FlagAsActiveCamera(bool isActiveCamera) { m_IsActiveCamera = isActiveCamera; }

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

protected:
	void DrawCustomEditor() override;

private:
	bool m_IsActiveCamera = false;

	glm::vec2 m_AspectRatio;
	int m_FieldOfView;
	float m_NearPlane;
	float m_FarPlane;

	Transform* m_ObjectTransform = nullptr;
};

REGISTER_COMPONENT(Camera)