#include "MeshComponent.h"

#include "TransformComponent.h"
#include "../Object.h"

namespace Forgex::Scene
{
    MeshComponent::MeshComponent() : Component("Mesh"), IRenderObject() {}

    MeshComponent::~MeshComponent() {}

    void MeshComponent::SetMesh(const std::vector<float>& vertices, const std::vector<int>& indices, const std::vector<float>& UVs, int shaderID,
                                int textureID)
    {
        m_Vertices.clear();
        m_Indices.clear();
        m_Vertices.reserve(vertices.size());
        m_Indices.reserve(indices.size());
        m_UVs.reserve(UVs.size());
        m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());
        m_Indices.insert(m_Indices.end(), indices.begin(), indices.end());
        m_UVs.insert(m_UVs.end(), UVs.begin(), UVs.end());
        
        m_ShaderID = shaderID;
        m_TextureID = textureID;
    }
}
