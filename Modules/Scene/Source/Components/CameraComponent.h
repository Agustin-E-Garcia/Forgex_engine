#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace Forgex::Scene
{
	class TransformComponent;

	struct AspectRatio{ float x, y; };
	
	class SCENE_API CameraComponent : public Component
	{
	public:
		CameraComponent();
		~CameraComponent();
	
		void FlagAsActiveCamera(bool isActiveCamera) { m_IsActiveCamera = isActiveCamera; }
	
		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetViewMatrix() const;

		void OnAttach() override;
		
	private:
        bool m_IsActiveCamera = false;
        float m_FieldOfView = 90.0f;

		AspectRatio m_AspectRatio;
		float m_NearPlane;
		float m_FarPlane;
	
		TransformComponent* m_ObjectTransform = nullptr;
	};
}
