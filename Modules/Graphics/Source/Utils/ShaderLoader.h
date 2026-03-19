#pragma once
#include "../GraphicsExports.h"

namespace Forgex::Graphics::Utils
{
    class GRAPHICS_API ShaderLoader
    {
    public:
        static int LoadShader(const char* vertexShader, const char* fragmentShader);
        static void UnloadShader(unsigned int shaderID);
    };
}
