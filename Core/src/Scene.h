#pragma once
#include "Exports.h"
#include "Object.h"
#include "Renderer.h"
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

	template<class T, class... Args>
	T* CreateObject(Args&&... args)
	{
		static_assert(std::is_base_of<Object, T>::value, "T must inherit from Object");

		T* newObject = new T(std::forward<Args>(args)...);
		m_Hierarchy.push_back(newObject);

		return newObject;
	}

	template<class T>
	void DestroyObject(T* object) 
	{
		static_assert(std::is_base_of<Object, T>::value, "T must inherit from Object");

		auto it = std::find(m_Hierarchy.begin(), m_Hierarchy.end(), object);
		if (it != m_Hierarchy.end()) 
		{
			m_Hierarchy.erase(it);
			delete object;
		}
	}

	template<class T>
	T* GetObjectOfType() const
	{
		static_assert(std::is_base_of<Object, T>::value, "T must inherit from Object");

		for (Object* obj : m_Hierarchy)
		{
			if (T* castedObject = dynamic_cast<T*>(obj)) return castedObject;
		}

		return nullptr;
	}

	template<class T>
	std::vector<T*> GetObjectCollectionOfType() const
	{
		static_assert(std::is_base_of<Object, T>::value, "T must inherit from Object");

		std::vector<T*> collection;
		for (Object* obj : m_Hierarchy)
		{
			if (T* castedObject = dynamic_cast<T*>(obj)) collection.push_back(castedObject);
		}

		return collection;
	}

private:
	const char* m_Name;
	std::vector<Object*> m_Hierarchy;
};