#include "SceneRenderProxy.h"
#include "Utils/BufferManager.h"
#include <algorithm>

namespace Forgex::Graphics
{
    SceneRenderProxy::SceneRenderProxy() = default;
    SceneRenderProxy::~SceneRenderProxy() = default;
    
    void SceneRenderProxy::SyncRenderObject(unsigned int uid, const std::vector<float>* vertex, const std::vector<int>* index, const std::vector<float>* uvs,
                                            int shaderID, int textureID, Math::Mat4 model)
    {
        // For now we do this, will change in the future
        RemoveRenderObject(uid);
        AddRenderObject(uid, vertex, index, uvs, shaderID, textureID, model);
        m_ShouldRebakeObjectData = true;
    }

    void SceneRenderProxy::Bake()
    {
        if(m_ShouldRebakeObjectData)
        {
            if(m_VertexBufferID == -1)
                m_VertexBufferID = Utils::BufferManager::GenerateBuffer
                (
                    Utils::VertexBuffer,
                    sizeof(float) * m_VertexBufferData.size(),
                    m_VertexBufferData.data()
                );

            if(m_IndexBufferID == -1)
                m_IndexBufferID = Utils::BufferManager::GenerateBuffer
                (
                    Utils::IndexBuffer,
                    sizeof(int) * m_IndexBufferData.size(),
                    m_IndexBufferData.data()
                );

            if(m_UVBufferID == -1)
                m_UVBufferID = Utils::BufferManager::GenerateBuffer
                (
                    Utils::UVBuffer,
                    sizeof(float) * m_UVBufferData.size(),
                    m_UVBufferData.data()
                );

            m_ShouldRebakeObjectData = false;
        }
    }

    void SceneRenderProxy::AddRenderObject(unsigned int uid, const std::vector<float>* vertex, const std::vector<int>* index, const std::vector<float>* uvs,
                                            int shaderID, int textureID, const Math::Mat4 model)
    {
        auto it = std::find(m_RenderObjectCollection.begin(),
                                                      m_RenderObjectCollection.end(),
                                                      uid);
        
        if(it != m_RenderObjectCollection.end()) return;
        
        RenderObjectInfo info;
        info.m_UID = uid;
        info.m_VertexBufferOffset = m_VertexBufferData.size();
        info.m_IndexBufferOffset = m_IndexBufferData.size();
        info.m_UVBufferOffset = m_UVBufferData.size();
        info.m_VertexCount = vertex->size();
        info.m_IndexCount = index->size();
        info.m_uvCount = uvs->size();
        info.m_ShaderID = shaderID;
        info.m_TextureID = textureID;
        info.m_ModelMatrix = model;

        m_VertexBufferData.insert(m_VertexBufferData.end(), vertex->begin(), vertex->end());
        m_IndexBufferData.insert(m_IndexBufferData.end(), index->begin(), index->end());
        m_UVBufferData.insert(m_UVBufferData.end(), uvs->begin(), uvs->end());
        m_RenderObjectCollection.push_back(info);
    }

    void SceneRenderProxy::RemoveRenderObject(unsigned int uid)
    {
        auto it = std::find(m_RenderObjectCollection.begin(), m_RenderObjectCollection.end(), uid);
        if(it != m_RenderObjectCollection.end())
        {
            const std::vector<float>::const_iterator firstVertex = m_VertexBufferData.begin() + it->m_VertexBufferOffset;
            const std::vector<float>::const_iterator lastVertex = m_VertexBufferData.begin() + it->m_VertexCount;
            m_VertexBufferData.erase(firstVertex, lastVertex);

            const std::vector<int>::const_iterator firstIndex = m_IndexBufferData.begin() + it->m_IndexBufferOffset;
            const std::vector<int>::const_iterator lastIndex = m_IndexBufferData.begin() + it->m_IndexCount;
            m_IndexBufferData.erase(firstIndex, lastIndex);

            const std::vector<float>::const_iterator firstUV = m_UVBufferData.begin() + it->m_UVBufferOffset;
            const std::vector<float>::const_iterator lastUV = m_UVBufferData.begin() + it->m_uvCount;
            m_UVBufferData.erase(firstUV, lastUV);
            
            m_RenderObjectCollection.erase(it);
        }
    }
}
