#include "GraphicsModule.h"
#include "Window.h"
#include <GL/glew.h>

namespace Forgex::Graphics
{
    void GraphicsModule::Init(Core::EngineCore& core)
    {
        core.SetWindow(new Window(1920, 1080, "Forgex Engine"));

        glewExperimental = true;
        GLenum result = glewInit();
        if (result != GLEW_OK)
        {
            const char* error = (const char*)glewGetErrorString(result);
            LOG_CORE(Debug::LogLevel::Critical, "Failed to initialize GLEW: {0}", error);
        }
    }

    void GraphicsModule::Update(float deltatime) {}

    void GraphicsModule::Shutdown() {}
}
