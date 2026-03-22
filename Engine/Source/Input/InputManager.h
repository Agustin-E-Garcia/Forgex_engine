#pragma once
#include "glm/fwd.hpp"
#include <unordered_map>
#include <glm/glm.hpp>

namespace Forgex::Engine::Input
{
    class InputManager
    {
    public:
        InputManager() {}
        ~InputManager() {}

        void RegisterKeyState(int keycode, bool isDown) { m_KeyState[keycode] = isDown; }
        void ResetMouseDelta() { m_MouseDelta = glm::dvec2(0.0f); }
        void UpdateMouseDelta(glm::dvec2 mousePos)
        {
            if (m_MouseInitialized)
                m_MouseDelta = mousePos - m_MousePosition;
            else
                m_MouseInitialized = true;
            m_MousePosition = mousePos;
        }

        bool IsKeyPressed(int keycode)
        {
            if(m_KeyState.contains(keycode)) return m_KeyState[keycode];
            return false;
        }

        glm::dvec2 GetMouseDelta() const { return m_MouseDelta; }

    private:
        std::unordered_map<int, bool> m_KeyState;
        glm::dvec2 m_MouseDelta = glm::dvec2(0.0f);
        glm::dvec2 m_MousePosition = glm::dvec2(0.0f);
        bool m_MouseInitialized = false;
    };
}
