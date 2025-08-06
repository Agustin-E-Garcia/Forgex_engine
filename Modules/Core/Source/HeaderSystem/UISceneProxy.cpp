#include "UISceneProxy.h"
#include <ForgexScene.h>
#include <cstdint>
#include <ForgexMath.h>

namespace Forgex::Core
{
	ObjectEntry GenerateObjectEntry(const Scene::Object* obj)
	{
		ObjectEntry newEntry(obj->GetName(), obj->GetUID());

		//TODO: Need to make a proxy of all the components this object has as to know how to draw them in the inspector without exposing Scene_Module to Forgex_Editor
        for(Scene::Component* component : *obj)
        {
            ComponentData data;
            data.m_Name = component->GetName();

            if(Scene::TransformComponent* transform = dynamic_cast<Scene::TransformComponent*>(component))
            {
                data.m_Variables.emplace_back("Position", VariableType::Vector3, transform->m_PositionPtr());
                data.m_Variables.emplace_back("Rotation", VariableType::Vector3, transform->m_RotationPtr());
                data.m_Variables.emplace_back("Scale", VariableType::Vector3, transform->m_ScalePtr());
            }
            else if(Scene::CameraComponent* camera = dynamic_cast<Scene::CameraComponent*>(component))
            {
                data.m_Variables.emplace_back("Active Camera", VariableType::Bool, camera->m_IsActiveCameraPtr());
                data.m_Variables.emplace_back("Field of View", VariableType::Float, camera->m_FieldOfViewPtr());
            }
            newEntry.m_ComponentData.push_back(data);
        }

		return newEntry;
	}
	
	UISceneProxy::UISceneProxy() : m_Initialized(false) {}
	UISceneProxy::~UISceneProxy() {}

    ObjectEntry UISceneProxy::GetObjectByID(uint32_t uid) const
    {
		for (int i = 0; i < m_ObjectCollection.size(); i++)
		{
			if (uid == m_ObjectCollection[i].m_ObjectID)
                return m_ObjectCollection[i];
		}

        return ObjectEntry("default", 0);
    }

	void UISceneProxy::SyncScene(Scene::Scene& scene)
	{
		if (m_Initialized && scene.GetName() == m_SceneName)
		{
			while(!m_CreateObjectQueue.empty())
			{
				m_ObjectCollection.emplace_back(GenerateObjectEntry(scene.CreateObject(m_CreateObjectQueue.front())));
				m_CreateObjectQueue.pop();
			}

			while(!m_DeleteObjectQueue.empty())
			{
				uint32_t uid = m_DeleteObjectQueue.front();
				scene.DestroyObject(scene.FindObjectByID(uid));

				for (int i = 0; i < m_ObjectCollection.size(); i++)
				{
					if (uid == m_ObjectCollection[i].m_ObjectID)
						m_ObjectCollection.erase(m_ObjectCollection.begin() + i);
				}

				m_DeleteObjectQueue.pop();
			}
		}
		else
		{
			m_SceneName = scene.GetName();
			m_ObjectCollection.clear();
			for (const Scene::Object& obj : scene)
			{
				m_ObjectCollection.emplace_back(GenerateObjectEntry(&obj));
			}
			m_Initialized = true;
		}
	}

	void UISceneProxy::QueueDeleteOrder(uint32_t objectID) { m_DeleteObjectQueue.push(objectID); }
	void UISceneProxy::QueueCreateOrder(std::string objectName) { m_CreateObjectQueue.push(objectName); }
}
