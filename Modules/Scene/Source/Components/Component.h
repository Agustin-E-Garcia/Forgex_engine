#pragma once
#include "../SceneExports.h"

namespace Forgex::Scene
{
	class Object;

	class SCENE_API Component
	{
	public:
		Component(const char* name) : m_Name(name) {}
		virtual ~Component() = default;

		virtual void Update(float deltaTime) {}

		const char* GetName() const { return m_Name; }
		const Object* GetOwner() const { return m_Owner; }
	
		void SetOwner(const Object* owner) { m_Owner = owner; OnAttach(); }

		virtual void OnAttach() {}
	protected:
		const char* m_Name;
		const Object* m_Owner = nullptr;
	};
}
