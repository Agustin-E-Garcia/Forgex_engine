#pragma once
#include "Component.h"

namespace Forgex::Math { struct UVec2; struct Mat4; }

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
	
		Math::Mat4 GetProjectionMatrix() const;
		Math::Mat4 GetViewMatrix() const;

		void OnAttach() override;
		
	private:
        CREATE_UI_VARIABLE(m_IsActiveCamera, bool, false)
        CREATE_UI_VARIABLE(m_FieldOfView, float)

		AspectRatio m_AspectRatio;
		float m_NearPlane;
		float m_FarPlane;
	
		TransformComponent* m_ObjectTransform = nullptr;
	};
}
