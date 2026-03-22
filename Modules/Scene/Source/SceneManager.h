#pragma once
#include <ForgexCore.h>
#include "Scene.h"

namespace Forgex::Scene
{
    class SceneManager
    {
    public:
        SceneManager(Core::Registry<Core::Interfaces::ISystem>& systemRegistry);
        ~SceneManager();

        void LoadScene(Scene* newScene);

        void Update(float deltaTime);
        void Render();

        Scene* GetActiveScene() { return m_ActiveScene; }

    private:
        Core::Registry<Core::Interfaces::ISystem>& m_SystemRegistry;
        Scene* m_ActiveScene;
    };
}
