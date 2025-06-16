#pragma once
#include "Object.h"
#include <vector>
#include <ForgexMath.h>

namespace Forgex::Scene
{
	class SCENE_API Scene
	{
	public:
		Scene(const char* name) : m_Name(name) {}
		~Scene() {}

		void Update(float deltaTime)
		{
			for (Object& obj : m_Hierarchy)
			{
				obj.Update(deltaTime);
			}
		}

		const char* GetName() const { return m_Name; }

		Object* CreateObject(std::string name, Math::Vec3 position = Math::Vec3::Zero(),  Object* parent = nullptr)
		{
			Object& obj = m_Hierarchy.emplace_back(name, position, this);

			if(parent)
			{
				obj.SetParent(parent);
				parent->AddChildObject(&obj);
			}
			
			return &obj;
		}

		void DestroyObject(Object* object)
		{
			if (!object) return;
		
			for (int i = 0; i < m_Hierarchy.size(); i++)
			{
				if (m_Hierarchy[i].GetUID() == object->GetUID())
					m_Hierarchy.erase(m_Hierarchy.begin() + i);
			}
		}

		template<class T>
		T* GetComponentOfType() 
		{
			for (Object& obj : m_Hierarchy) 
			{
				T* component = obj.GetComponentOfType<T>();
				if (component) return component;
			}

			return nullptr;
		}

		Object* FindObjectByID(uint32_t id) 
		{
			for (Object& obj : m_Hierarchy)
			{
				if (obj.GetUID() == id) return &obj;
			}

			return nullptr;
		}

		std::vector<Object>::const_iterator begin() const { return m_Hierarchy.cbegin(); }
		std::vector<Object>::const_iterator end() const { return m_Hierarchy.cend(); }
		
	private:
		const char* m_Name;
		std::vector<Object> m_Hierarchy;
	};
}
