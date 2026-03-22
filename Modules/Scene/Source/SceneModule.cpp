#include "SceneModule.h"
#include "SceneManager.h"

namespace Forgex::Scene
{
    void SceneModule::Init(Core::EngineCore& core) { Core::ServiceLocator::Get().Register<SceneManager>(core.GetSystemRegistry()); }
    void SceneModule::Shutdown() {}
}
