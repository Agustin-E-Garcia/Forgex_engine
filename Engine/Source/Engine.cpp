#include "Engine.h"
#include "GameLayer.h"
#include "Input/InputManager.h"
#include "Input/InputSystem.h"

#include <ForgexGraphics.h>
#include <ForgexScene.h>
#include <ForgexVoxel.h>

namespace Forgex::Engine
{
    Engine::Engine()
    {
        m_EngineCore = new Core::EngineCore();
        m_EngineCore->RegisterModule<Graphics::GraphicsModule>();
        m_EngineCore->RegisterModule<Scene::SceneModule>();
        m_EngineCore->RegisterModule<Voxel::VoxelModule>();

        Core::ServiceLocator::Get().Register<Input::InputManager>();
        m_EngineCore->RegisterSystem<Input::InputSystem>();
        PushLayer(new GameLayer());

        m_EngineCore->Run();
    }

    Engine::~Engine() { delete m_EngineCore; }

    void Engine::PushLayer(Core::Layer::Layer* layer) { m_EngineCore->RegisterLayer(layer); }
    void Engine::PushOverlay(Core::Layer::Layer* overlay) { m_EngineCore->RegisterOverlay(overlay); }
}
