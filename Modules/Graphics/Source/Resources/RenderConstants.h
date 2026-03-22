#pragma once
#include <vector>
#include "../Utils/BufferManager.h"
#include "../AssetTypes/ShaderAsset.h"
#include "../Utils/TextureLoader.h"

#include <ForgexAssets.h>
#include <ForgexCore.h>

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
        int g_VertexBufferID = INVALID_ID;
        Assets::AssetHandle<ShaderAsset> g_ShaderHandle;
        int g_DefaultTextureID = INVALID_ID;
 
        const char* g_SkyboxShaderPath = "Resources/Shaders/Skybox.FShader";
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

            if(!g_ShaderHandle.IsValid()) g_ShaderHandle = Core::ServiceLocator::Get().Fetch<Assets::AssetManager>()->LoadAsset<ShaderAsset>(g_SkyboxShaderPath);

            if(g_DefaultTextureID == INVALID_ID) g_DefaultTextureID = Utils::TextureLoader::LoadCubemapTexture(Utils::TextureType::Cubemap, g_DefaultSkyboxTextures);
        }
    }
};
