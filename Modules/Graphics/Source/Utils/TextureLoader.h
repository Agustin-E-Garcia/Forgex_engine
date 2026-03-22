#pragma once
#include <vector>

namespace Forgex::Graphics::Utils
{
    enum TextureType
    {
        Default = 0,
        Cubemap = 1
    };

    class TextureLoader
    {
    public:
        static int LoadDefaultTexture(TextureType type, const char* filePaths);
        static int LoadCubemapTexture(TextureType type, std::vector<const char*> filePaths);
        static void UnloadTexture(unsigned int textureID);
    };
}
