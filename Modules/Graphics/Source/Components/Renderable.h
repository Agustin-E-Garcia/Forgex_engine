#pragma once
#include "../GraphicsExports.h"
#include "../AssetTypes/ShaderAsset.h"
#include "../AssetTypes/TextureAsset.h"
#include <glm/glm.hpp>

namespace Forgex::Graphics
{
    struct GRAPHICS_API Renderable
    {
        float* m_Vertices = nullptr; // x, y, z, nx, ny, nz
        int m_VertexSize = 0;
        int* m_Indices = nullptr; // Indices
        int m_IndexSize = 0;

        Assets::AssetHandle<ShaderAsset> m_ShaderAsset;
        Assets::AssetHandle<TextureAsset> m_TextureAsset;

        glm::mat4 m_ModelMatrix;

        int m_VertexBufferID = -1;
        int m_IndexBufferID = -1;
    };
}
