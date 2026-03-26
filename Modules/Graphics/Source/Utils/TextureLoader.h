#pragma once
#include <string>
#include <vector>
#include <ForgexAssets.h>
#include <ForgexFiles.h>

namespace Forgex::Graphics::Utils
{
    class TextureLoader
    {
    public:
        static int LoadTexture(const char* file, Files::TextureData& data);
        static int LoadTexture(std::vector<std::string> filePaths, Files::TextureData& data);
        static void UnloadTexture(unsigned int textureID);
    };
}
