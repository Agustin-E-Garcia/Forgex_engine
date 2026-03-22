#include "Editor.h"
#include "UI/UILayer.h"
#include <ForgexEngine.h>

namespace Forgex::Editor
{
    Editor::Editor() 
    { 
        Engine::Engine engineInstance;
        engineInstance.PushOverlay(new UI::UIOverlay());
    }

    Editor::~Editor() {}
}
