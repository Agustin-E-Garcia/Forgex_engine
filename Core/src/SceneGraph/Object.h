#pragma once
#include "../Exports.h"
#include "Component.h"
#include <string>
#include <vector>

class Scene;
class Transform;

class ENGINE_API Object
{
public:
	Object(std::string name, glm::vec3 position, Scene* ownerScene);
	~Object();

	inline uint32_t GetUID() const { return m_UniqueIdentifier; }
	inline const std::string GetName() const { return m_Name; }
	inline Transform* GetTransform() const { return m_Transform; }
	inline std::vector<Component*> GetComponentList() const { return m_Components; }
	inline Scene* GetScene() { return m_OwnerScene; }
	
	inline void ChangeName(std::string newName) { m_Name = newName; }

	void DrawEditor();
	virtual void Update(float deltaTime);
	virtual void Render(const Renderer& renderer);

	template<class T, class... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");		
		Component* component = m_Components.emplace_back(new T(std::forward<Args>(args)...));
		component->SetParent(this);

		return dynamic_cast<T*>(component);
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

	void RemoveComponent(Component* component);

private:
	std::string m_Name;
	uint32_t m_UniqueIdentifier;
	
	std::vector<Component*> m_Components;
	Transform* m_Transform;
	Scene* m_OwnerScene;
};