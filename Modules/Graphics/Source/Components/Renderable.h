#pragma once
#include "../AssetTypes/ShaderAsset.h"
#include "../AssetTypes/TextureAsset.h"
#include "../AssetTypes/MeshAsset.h"
#include <glm/glm.hpp>

namespace Forgex::Graphics::Components
{
    struct Renderable
    {
        Assets::AssetHandle<ShaderAsset> m_ShaderAsset;
        Assets::AssetHandle<TextureAsset> m_TextureAsset;
        Assets::AssetHandle<MeshAsset> m_MeshAsset;

        glm::mat4 m_ModelMatrix;
   };
}
