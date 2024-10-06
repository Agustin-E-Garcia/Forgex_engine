#pragma once
#include "../Exports.h"
#include "Object.h"
#include "../Renderer.h"
#include <vector>
#include <utility>

class ENGINE_API Scene
{
public:
	Scene(const char* name) : m_Name(name) {};
	
	~Scene() 
	{
		for (auto it = m_Hierarchy.begin(); it != m_Hierarchy.end();)
		{
			delete *it;
			it = m_Hierarchy.erase(it);
		}
	};

	void Update(float deltaTime)
	{
		for (Object* obj : m_Hierarchy)
		{
			obj->Update(deltaTime);
		}
	}

	void Render(const Renderer& renderer) 
	{
		for (Object* obj : m_Hierarchy)
		{
			obj->Render(renderer);
		}
	}

	inline const char* GetName() const { return m_Name; }
	inline std::vector<Object*> GetHierarchy() const { return m_Hierarchy; }

	inline Object* CreateObject(std::string name, glm::vec3 position = glm::vec3(0))
	{
		return m_Hierarchy.emplace_back(new Object(name, position, this));
	}

	inline void DestroyObject(Object* object) 
	{
		if (!object) return;

		auto it = std::find(m_Hierarchy.begin(), m_Hierarchy.end(), object);
		if (it != m_Hierarchy.end()) 
		{
			delete* it;
			m_Hierarchy.erase(it);
		}
	}

	template<class T>
	T* GetComponentOfType() 
	{
		for (Object* obj : m_Hierarchy) 
		{
			T* component = obj->GetComponentOfType<T>();
			if (component) return component;
		}

		return nullptr;
	}

	Object* FindObjectByID(uint32_t id) 
	{
		for (Object* obj : m_Hierarchy)
		{
			if (obj->GetUID() == id) return obj;
		}

		return nullptr;
	}

private:
	const char* m_Name;
	std::vector<Object*> m_Hierarchy;
};