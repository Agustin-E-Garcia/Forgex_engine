#pragma once
#include <glm/glm.hpp>

namespace Forgex::Graphics::Resources
{
    struct RenderInfo
    {
        int m_ShaderID;
        int m_TextureID;
        glm::mat4 m_ModelMatrix;
        int m_VertexBufferID;
        int m_IndexBufferID;
        int m_IndexCount;

        RenderInfo(int shaderID, int textureID, glm::mat4 modelMatrix, int vertexBufferID, int indexBufferID, int indexCount)
            : m_ShaderID(shaderID), m_TextureID(textureID), m_ModelMatrix(modelMatrix), m_VertexBufferID(vertexBufferID), m_IndexBufferID(indexBufferID), m_IndexCount(indexCount) {}
    };
}
