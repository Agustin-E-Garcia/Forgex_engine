#pragma once
#include "../SceneExports.h"
#include <vector>
#include <ForgexMath.h>


namespace Forgex::Scene
{
    class SCENE_API IRenderObject
    {
    public:
        const std::vector<float>* GetVertices() const { return &m_Vertices; }
        const std::vector<int>* GetIndices() const { return &m_Indices; }
        const std::vector<float>* GetUVs() const { return &m_UVs; }
        const std::vector<Math::Mat4>* GetMatrices() const { return &m_ModelMatrices; }
        int GetShaderID() const { return m_ShaderID; }
        int GetTextureID() const { return m_TextureID; }

        void AssignShader(int shaderID) { m_ShaderID = shaderID; }
        void AssignTexture(int textureID) { m_TextureID = textureID; }
    
    protected:
        IRenderObject() {}
        
        std::vector<float> m_Vertices;
        std::vector<int> m_Indices;
        std::vector<float> m_UVs;
        std::vector<Math::Mat4> m_ModelMatrices;

        int m_ShaderID = -1;
        int m_TextureID = -1;
    };
}
