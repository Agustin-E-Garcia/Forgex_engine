#pragma once
#include <string>
#include <vector>

namespace Forgex::Graphics::Utils
{
    class TextureLoader
    {
    public:
        static int LoadTexture(const char* filePaths);
        static int LoadTexture(std::vector<std::string> filePaths);
        static void UnloadTexture(unsigned int textureID);
    };
}
