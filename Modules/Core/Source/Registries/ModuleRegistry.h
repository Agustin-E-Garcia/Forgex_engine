#pragma once
#include <vector>
#include <string>
#include "../Interfaces/IModule.h"

namespace Forgex::Core { class EngineCore; }

namespace Forgex::Core::Registries
{
    class ModuleRegistry
    {
    public:
        void RegisterModule(Interfaces::IModule* module) { m_Modules.push_back(module); }

        void InitAll(EngineCore& core)
        {
            for (auto* m : m_Modules)
                m->Init(core);
        }

        void UpdateAll(float deltaTime)
        {
            for (auto* m : m_Modules)
                m->Update(deltaTime);
        }

        void ShutdownAll()
        {
            for (auto* m : m_Modules)
                m->Shutdown();
        }

        Interfaces::IModule* GetModule(const std::string& name) const
        {
            for (auto* m : m_Modules)
                if (m->GetName() == name)
                    return m;
            return nullptr;
        }

        const std::vector<Interfaces::IModule*>& GetModules() const { return m_Modules; }

        std::vector<Interfaces::IModule*>::iterator begin() { return m_Modules.begin(); }
        std::vector<Interfaces::IModule*>::iterator end() { return m_Modules.end(); }

    private:
        std::vector<Interfaces::IModule*> m_Modules;
    };
}
