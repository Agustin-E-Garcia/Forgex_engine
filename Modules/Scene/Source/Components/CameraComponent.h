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
		bool m_IsActiveCamera = false;
	
		AspectRatio m_AspectRatio;
		int m_FieldOfView;
		float m_NearPlane;
		float m_FarPlane;
	
		TransformComponent* m_ObjectTransform = nullptr;
	};
}