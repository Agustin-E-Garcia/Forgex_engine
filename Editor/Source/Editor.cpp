#include "Editor.h"
#include "UI/UIOverlay.h"
#include <ForgexEngine.h>

namespace Forgex::Editor
{
    Editor::Editor()
    {
        Engine::Engine engineInstance;
        engineInstance.PushOverlay(new UI::UIOverlay());
        engineInstance.Run();
    }

    Editor::~Editor() {}
}
