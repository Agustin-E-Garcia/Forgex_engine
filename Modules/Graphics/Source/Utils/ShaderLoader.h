#pragma once

namespace Forgex::Graphics::Utils
{
    class ShaderLoader
    {
    public:
        static int LoadShader(const char* vertexShader, const char* fragmentShader);
        static void UnloadShader(unsigned int shaderID);
    };
}
