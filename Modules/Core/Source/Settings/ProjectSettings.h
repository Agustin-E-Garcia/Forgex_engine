#pragma once
#include "../CoreExports.h"
#include "../Interfaces/ISettings.h"
#include "../Registry.h"

namespace Forgex::Core::Settings
{
    class CORE_API ProjectSettings
    {
    public:
        template<class T>
        void RegisterSettings() { m_Settings.Register<T>(); }

        template<class T>
        T* GetSettings() { return m_Settings.Get<T>(); }

    private:
        Registry<Interfaces::ISettings> m_Settings;
    };
}
