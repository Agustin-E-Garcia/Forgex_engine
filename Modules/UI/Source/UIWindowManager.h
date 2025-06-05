#pragma once
#include "UIExport.h"
#include "GUIWindow.h"
#include <vector>

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

	template<class T, class... Args>
	unsigned int AddWindow(Args&&... args)
	{
		static_assert(std::is_base_of<GUIWindow, T>::value, "T must inherit from GUIWindow");		
		unsigned int index = m_WindowCollection.size();
		m_WindowCollection.emplace_back(T(std::forward<Args>(args)...));
		return index;
	}

        void UpdateMousePosition(double xPos, double yPos);
        void OnMouseClick(unsigned int button, bool clicked);
        void OnMouseWheelScroll(double xOffset, double yOffset);
        void OnCharInput(unsigned int keycode);
        void OnKeyPressed(unsigned int keycode, bool repeat, bool pressed);
        void OnWindowResized(int width, int height);

    private:
        void* m_ActiveContext = nullptr;
        bool m_WindowActive = true;
	std::vector<GUIWindow> m_WindowCollection;
    };

    static UIWindowManager* CreateWindowManager() { return new UIWindowManager(); }
}
