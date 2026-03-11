#pragma once

namespace Forgex::Scene 
{
    struct Render
    {
        int m_ShaderID = -1;
        int m_TextureID = -1;
        float* m_Vertices = nullptr; // x, y, z, u, v
        int m_VertexSize = 0;
        int* m_Indices = nullptr; // Indices
        int m_IndexSize = 0;

        int m_VertexBufferID = -1;
        int m_IndexBufferID = -1;
    };
}
