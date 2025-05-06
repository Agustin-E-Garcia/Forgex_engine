#pragma once
#include "UIExport.h"

namespace Forgex::UI
{
    class UI_DLL UIWindowManager
    {
    public:
        UIWindowManager();
        ~UIWindowManager();

        void SetContext();
        void Update(float deltaTime);
        void Render();
        
    private:
        void* m_ImGuiContext = nullptr;
        bool m_WindowActive = true;
    };

    static UIWindowManager* CreateWindowManager() { return new UIWindowManager(); }
}