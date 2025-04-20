#pragma once
#include "GraphicsExports.h"
#include <vector>
#include <ForgexMath.h>

namespace Forgex::Graphics
{
    struct RenderObjectInfo
    {
        unsigned int m_UID = 0;
        int m_VertexBufferOffset = -1;
        int m_IndexBufferOffset = -1;
        int m_UVBufferOffset = -1;
        int m_VertexCount = -1;
        int m_IndexCount = -1;
        int m_uvCount = -1;
        int m_ShaderID = -1;
        int m_TextureID = -1;
        Math::Mat4 m_ModelMatrix = Math::Mat4(1.0f);

        bool operator==(const RenderObjectInfo& other) const { return m_UID == other.m_UID; }
        bool operator==(const unsigned int& other) const { return m_UID == other; }
    };
    
    class GRAPHICS_API SceneRenderProxy
    {
    public:
        SceneRenderProxy();
        ~SceneRenderProxy();
        
        void SyncRenderObject(unsigned int uid, const std::vector<float>* vertex, const std::vector<int>* index,
            const std::vector<float>* uvs, int shaderID, int textureID, Math::Mat4 model);

        void Bake();

        const std::vector<RenderObjectInfo>* GetRenderObjectCollection() const { return &m_RenderObjectCollection; }
        
        int GetVertexBufferID() const { return m_VertexBufferID; }
        int GetIndexBufferID() const { return m_IndexBufferID; }
        int GetUVBufferID() const { return m_UVBufferID; }
        
    private:
        void AddRenderObject(unsigned int uid, const std::vector<float>* vertex, const std::vector<int>* index, const std::vector<float>* uvs,
                                    int shaderID, int textureID, const Math::Mat4 model);
        void RemoveRenderObject(unsigned int uid);

        bool m_ShouldRebakeObjectData = false;
        
        std::vector<float> m_VertexBufferData;
        std::vector<int> m_IndexBufferData;
        std::vector<float> m_UVBufferData;
        
        std::vector<RenderObjectInfo> m_RenderObjectCollection;
        
        int m_VertexBufferID = -1;
        int m_IndexBufferID = -1;
        int m_UVBufferID = -1;
    };
}