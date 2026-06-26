#pragma once
#include "../CoreExports.h"
#include "../Interfaces/ISettings.h"

#include <ForgexDataStructures.h>

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
        DataStructures::Registry<Interfaces::ISettings> m_Settings;
    };
}
