#include "Editor.h"
#include "UI/UIOverlay.h"
#include "Systems/GizmoSystem.h"
#include <ForgexEngine.h>

namespace Forgex::Editor
{
    Editor::Editor()
    {
        Engine::Engine engineInstance;
        engineInstance.PushOverlay(new UI::UIOverlay());
        engineInstance.RegisterSystem<Systems::GizmoSystem>();
        engineInstance.Run();
    }

    Editor::~Editor() {}
}
