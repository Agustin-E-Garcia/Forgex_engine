#pragma once
#include "Component.h"
#include "IRenderObject.h"

namespace Forgex::Scene
{
    class SCENE_API MeshComponent : public Component, public IRenderObject
    {
    public:
        MeshComponent();
        ~MeshComponent() override;
        
        void SetMesh(const std::vector<float>& vertices, const std::vector<int>& indices, const std::vector<float>& UVs, int shaderID, int textureID);
    };
}
