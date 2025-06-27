#pragma once
#include "CoreExports.h"
#include <stdint.h>
#include <string>
#include <queue>
#include <vector>
#include <map>

namespace Forgex::Scene { class Scene; }

namespace Forgex::Core
{
	enum CORE_API VariableType
	{
		Text, Float, Int, Vector3, Vector2
	};

	struct CORE_API VariableData
	{
		const char* m_Name;
		const void* m_DataPtr;
		const VariableType m_Type;

		VariableData(const char* name, void* ptr, VariableType type) : m_Name(name), m_DataPtr(ptr), m_Type(type) {}
	};

	struct CORE_API ObjectEntry
	{
		std::string m_ObjectName;
		unsigned int m_ObjectID;
		std::map<const char*, std::vector<VariableData>> m_ComponentData;

		ObjectEntry(std::string name, unsigned int UID)
		{ 
			m_ObjectName = name;
			m_ObjectID = UID;
		}
	};

	class CORE_API UISceneProxy
	{
	public:
		UISceneProxy();
		~UISceneProxy();

		void SyncScene(Scene::Scene& scene);
		void QueueDeleteOrder(uint32_t objectID);
		void QueueCreateOrder(std::string objectName);

		const char* GetName() const { return m_SceneName; }

		std::vector<ObjectEntry>::const_iterator begin() const { return m_ObjectCollection.cbegin(); }
		std::vector<ObjectEntry>::const_iterator end() const { return m_ObjectCollection.cend(); }
	private:
		bool m_Initialized = false;
		const char* m_SceneName;
		
		std::vector<ObjectEntry> m_ObjectCollection;
		std::queue<std::string> m_CreateObjectQueue;
		std::queue<uint32_t> m_DeleteObjectQueue;
	};
}
