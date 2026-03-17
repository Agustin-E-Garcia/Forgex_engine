#pragma once
#include <vector>
#include "../Utils/TextureLoader.h"
#include "../Utils/ShaderLoader.h"
#include "../Utils/BufferManager.h"

namespace Forgex::Graphics::Resources::Constants
{
    inline constexpr int INVALID_ID = -1;

    namespace RenderObjects
    {
        inline int vertexArrayID = INVALID_ID;

        inline void InitResources()
        {
            if(vertexArrayID == INVALID_ID) vertexArrayID = Utils::BufferManager::GenerateVBO();
        }
    }
 
    namespace Skybox
    {
        inline int g_ShaderID = INVALID_ID;
        inline int g_VertexBufferID = INVALID_ID;
        inline int g_DefaultTextureID = INVALID_ID;
 
        const char* g_SkyboxVertexShaderPath = "Resources/Shaders/Skybox.vertex";
        const char* g_SkyboxFragmentShaderPath = "Resources/Shaders/Skybox.fragment";
        inline const std::vector<const char*> g_DefaultSkyboxTextures =
        {
           "Resources/Textures/right.jpg",
           "Resources/Textures/left.jpg",
           "Resources/Textures/up.jpg",
           "Resources/Textures/down.jpg",
           "Resources/Textures/front.jpg",
           "Resources/Textures/back.jpg"
        };

        inline const std::vector<float> g_SkyboxVertices
        {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };


        inline void InitResources()
        {
            if(g_VertexBufferID == INVALID_ID) g_VertexBufferID = Utils::BufferManager::GenerateBuffer(Utils::BufferType::VertexBuffer,
                sizeof(float) * g_SkyboxVertices.size(), g_SkyboxVertices.data());

            if(g_ShaderID == INVALID_ID) g_ShaderID = Utils::ShaderLoader::LoadShader(g_SkyboxVertexShaderPath, g_SkyboxFragmentShaderPath);

            if(g_DefaultTextureID == INVALID_ID) g_DefaultTextureID = Utils::TextureLoader::LoadCubemapTexture(Utils::TextureType::Cubemap,
                                                                          g_DefaultSkyboxTextures);
        }
    }
};
