#pragma once
#include "../GraphicsExports.h"
#include "../AssetTypes/MeshAsset.h"
#include "../AssetTypes/MaterialAsset.h"
#include <glm/glm.hpp>

namespace Forgex::Graphics::Components
{
    struct GRAPHICS_API Renderable
    {
        Assets::AssetHandle<MeshAsset> m_MeshAsset;
        Assets::AssetHandle<MaterialAsset> m_MaterialAsset;

        glm::mat4 m_ModelMatrix;
   };
}
