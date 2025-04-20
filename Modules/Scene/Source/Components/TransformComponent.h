#pragma once
#include "Component.h"
#include <ForgexMath.h>

namespace Forgex::Scene
{
	class SCENE_API TransformComponent : public Component
	{
	public:
		TransformComponent();
		~TransformComponent();

		Math::Mat4 GetModelMatrix() const;

		Math::Vec3 GetPosition() const;
		Math::Vec3 GetRotation() const;
		Math::Vec3 GetScale() const;
	
		Math::Vec3 GetForward() const;
		Math::Vec3 GetRight() const;
		Math::Vec3 GetUp() const;

		void SetPosition(Math::Vec3 newPosition);
		void SetRotationX(float amount);
		void SetRotationY(float amount);
		void SetRotationZ(float amount);
		void SetScale(Math::Vec3 newScale);

	private:
		Math::Vec3 m_Position = Math::Vec3(0.0f);
		Math::Vec3 m_Rotation = Math::Vec3(0.0f);
		Math::Vec3 m_Scale = Math::Vec3(1.0f);
	
		Math::Vec3 m_Forward = Math::Vec3(0.0f, 0.0f, -1.0f);
		Math::Vec3 m_Right = Math::Vec3(1.0f, 0.0f, 0.0f);
		Math::Vec3 m_Up = Math::Vec3(0.0f, 1.0f, 0.0f);

		Math::Quat m_RotationQuat = Math::Quat(1.0f, 0.0f, 0.0f, 0.0f);

		Math::Mat4 m_ModelMatrix = Math::Mat4(1.0f);
		Math::Mat4 m_LocationMatrix = Math::Mat4(1.0f);
		Math::Mat4 m_ScaleMatrix = Math::Mat4(1.0f);
		Math::Mat4 m_RotationMatrix = Math::Mat4(1.0f);

		void UpdateModelMatrix();
		void UpdateVectors();
		void UpdateRotation();
	};
}