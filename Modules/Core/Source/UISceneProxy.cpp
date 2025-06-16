#include "UISceneProxy.h"
#include <ForgexScene.h>

namespace Forgex::Core
{
	UISceneProxy::UISceneProxy() : m_Initialized(false) {}
	UISceneProxy::~UISceneProxy() {}

	void UISceneProxy::SyncScene(Scene::Scene& scene)
	{
		if (m_Initialized && scene.GetName() == m_SceneName)
		{
			while(!m_CreateObjectQueue.empty())
			{
				Scene::Object* obj = scene.CreateObject(m_CreateObjectQueue.front());
				m_ObjectCollection.emplace_back(obj->GetName(), obj->GetUID());
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
				m_ObjectCollection.emplace_back(obj.GetName(), obj.GetUID());
			}
			m_Initialized = true;
		}
	}

	void UISceneProxy::QueueDeleteOrder(uint32_t objectID) { m_DeleteObjectQueue.push(objectID); }
	void UISceneProxy::QueueCreateOrder(std::string objectName) { m_CreateObjectQueue.push(objectName); }
}
