#pragma once
#include "UIExport.h"

namespace Forgex::UI
{
    class UI_API UIWindowManager
    {
    public:
        UIWindowManager();
        ~UIWindowManager();

        void SetContext();
        void Update(float deltaTime);
        void Render();

        void UpdateMousePosition(double xPos, double yPos);
        void OnMouseClick(unsigned int button, bool clicked);
        void OnMouseWheelScroll(double xOffset, double yOffset);
        void OnCharInput(unsigned int keycode);
        void OnKeyPressed(unsigned int keycode, bool repeat, bool pressed);
        void OnWindowResized(int width, int height);

    private:
        void* m_ActiveContext = nullptr;
        bool m_WindowActive = true;
    };

    static UIWindowManager* CreateWindowManager() { return new UIWindowManager(); }
}
