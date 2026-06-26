#pragma once
#include "SceneExports.h"
#include "Scene.h"

namespace Forgex::Scene
{
    class SCENE_API SceneManager
    {
    public:
        SceneManager(DataStructures::Registry<Core::Interfaces::ISystem>& systemRegistry);
        ~SceneManager();

        void LoadScene(Scene* newScene);

        void Setup();
        void Update(float deltaTime);
        void Render();

        Scene* GetActiveScene() { return m_ActiveScene; }

    private:
        DataStructures::Registry<Core::Interfaces::ISystem>& m_SystemRegistry;
        Scene* m_ActiveScene;
    };
}
