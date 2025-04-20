#pragma once
#include "Object.h"
#include <vector>
#include <utility>
#include <ForgexMath.h>

namespace Forgex::Scene
{
	class SCENE_API Scene
	{
	public:
		Scene(const char* name) : m_Name(name) {}
	
		~Scene() 
		{
			for (auto it = m_Hierarchy.begin(); it != m_Hierarchy.end();)
			{
				delete *it;
				it = m_Hierarchy.erase(it);
			}
		}

		void Update(float deltaTime)
		{
			for (Object* obj : m_Hierarchy)
			{
				obj->Update(deltaTime);
			}
		}

		const char* GetName() const { return m_Name; }
		const std::vector<Object*>* GetHierarchy() const { return &m_Hierarchy; }

		Object* CreateObject(std::string name,
							 Math::Vec3 position = Math::Vec3::Zero(),
							 Object* parent = nullptr)
		{
			Object* obj = m_Hierarchy.emplace_back(new Object(name, position, this));
			
			if(parent)
			{
				obj->SetParent(parent);
				parent->AddChildObject(obj);
			}
			
			return obj;
		}

		void DestroyObject(Object* object) 
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

		std::vector<Object*>::const_iterator begin() const { return m_Hierarchy.cbegin(); }
		std::vector<Object*>::const_iterator end() const { return m_Hierarchy.cend(); }
		
	private:
		const char* m_Name;
		std::vector<Object*> m_Hierarchy;
	};
}
