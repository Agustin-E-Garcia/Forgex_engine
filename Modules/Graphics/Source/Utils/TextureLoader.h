#pragma once
#include <string>
#include <vector>
#include <ForgexAssets.h>

namespace Forgex::Graphics::Utils
{
    class TextureLoader
    {
    public:
        static int LoadTexture(const char* file, Assets::Files::TextureData& data);
        static int LoadTexture(std::vector<std::string> filePaths, Assets::Files::TextureData& data);
        static void UnloadTexture(unsigned int textureID);
    };
}
