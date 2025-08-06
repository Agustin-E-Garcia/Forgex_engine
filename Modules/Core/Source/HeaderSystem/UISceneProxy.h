#pragma once
#include "../CoreExports.h"
#include <cstdint>
#include <stdint.h>
#include <string>
#include <queue>
#include <vector>

namespace Forgex::Scene { class Scene; }

namespace Forgex::Core
{
    enum CORE_API VariableType 
    {
        Text, Bool, Float, Vector3, UVector2
    };

    struct CORE_API VariableData 
    {
        std::string m_Name;
        VariableType m_Type;
        void* m_Ptr;

        VariableData(std::string name, VariableType type, void* ptr) : m_Name(name), m_Type(type), m_Ptr(ptr) {}
    };

    struct CORE_API ComponentData
    {
        std::string m_Name;
        std::vector<VariableData> m_Variables;
    };

	struct CORE_API ObjectEntry
	{
		std::string m_ObjectName;
		unsigned int m_ObjectID;
		std::vector<ComponentData> m_ComponentData;

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
        ObjectEntry GetObjectByID(uint32_t uid) const; 

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
