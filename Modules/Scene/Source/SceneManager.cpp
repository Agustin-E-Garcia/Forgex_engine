#include "SceneManager.h"

namespace Forgex::Scene
{
    SceneManager::SceneManager(DataStructures::Registry<Core::Interfaces::ISystem>& systemRegistry) : m_SystemRegistry(systemRegistry) {}
    SceneManager::~SceneManager() {}

    void SceneManager::LoadScene(Scene* newScene) { m_ActiveScene = newScene; }

    void SceneManager::Setup() { m_ActiveScene->Setup(m_SystemRegistry); }
    void SceneManager::Update(float deltaTime) { m_ActiveScene->Update(m_SystemRegistry, deltaTime); }
    void SceneManager::Render() { m_ActiveScene->Render(m_SystemRegistry); }
}
