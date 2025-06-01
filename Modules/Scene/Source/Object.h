#pragma once
#include "Components/Component.h"
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

namespace Forgex::Math { struct Vec3; }

namespace Forgex::Scene
{
	class Scene;
	class TransformComponent;

	class SCENE_API Object
	{
	public:
		Object(std::string name);
		Object(std::string name, Math::Vec3 position, Scene* ownerScene);
		~Object();

		uint32_t GetUID() const { return m_UniqueIdentifier; }
		const std::string GetName() const { return m_Name; }
		TransformComponent* GetTransform() const { return m_Transform; }
		const std::vector<Component*>* GetComponentList() const { return &m_Components; }
		const Scene* GetScene() const { return m_OwnerScene; }

		void SetParent(const Object* parent) { m_ParentObject = parent; }
		void AddChildObject(const Object* child) { m_ChildObjects.push_back(child); }
	
		void ChangeName(std::string newName) { m_Name = newName; }

		virtual void Update(float deltaTime);

		template<class T, class... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");		
			Component* component = m_Components.emplace_back(new T(std::forward<Args>(args)...));
			component->SetOwner(this);
		
			return dynamic_cast<T*>(component);
		}

		void RemoveComponent(Component* component)
		{
			auto it = std::find(m_Components.begin(), m_Components.end(), component);
			if (it != m_Components.end())
			{
				delete* it;
				m_Components.erase(it);
			}	
		}
	
		template<class T>
		T* GetComponentOfType()
		{
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
		
			for (Component* component : m_Components)
			{
				if (T* castedComponent = dynamic_cast<T*>(component)) return castedComponent;
			}
		
			return nullptr;
		}

		std::vector<Component*>::const_iterator begin() const { return m_Components.cbegin(); }
		std::vector<Component*>::const_iterator end() const { return m_Components.cend(); }
		
	private:
		std::string m_Name;
		uint32_t m_UniqueIdentifier;
		const Object* m_ParentObject;
	
		std::vector<Component*> m_Components;
		std::vector<const Object*> m_ChildObjects;
	
		TransformComponent* m_Transform;
		const Scene* m_OwnerScene;
	};
}
