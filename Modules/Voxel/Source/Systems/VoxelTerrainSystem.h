#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>

#include "../Components/VoxelChunk.h"
#include "../Utils/TerrainGenerator.h"
#include "../Utils/ChunkMesher.h"

namespace Forgex::Voxel::Systems
{
    class VoxelTerrainSystem : public Core::Interfaces::PerEntitySystem<Components::Chunk, Graphics::Components::Renderable>
    {
    public:
        void OnUpdate(float deltaTime, const entt::entity& entity, Components::Chunk& chunk, Graphics::Components::Renderable& renderable) override
        {
            if(chunk.m_IsDirty)
            {
                Utils::TerrainGenerator generator = Utils::TerrainGenerator(chunk.m_NoiseSeed);
                Utils::ChunkMesher mesher = Utils::ChunkMesher(&chunk, &generator);

                std::vector<float> vertices;
                std::vector<int> indices;
                mesher.GenerateMesh(vertices, indices);

                renderable.m_Vertices = vertices.data();
                renderable.m_VertexSize = vertices.size();

                renderable.m_Indices = indices.data();
                renderable.m_IndexSize = indices.size();

                renderable.m_VertexBufferID = Graphics::Utils::BufferManager::GenerateBuffer
                (
                    Graphics::Utils::BufferType::VertexBuffer,
                    renderable.m_VertexSize * sizeof(float),
                    renderable.m_Vertices
                );

                renderable.m_IndexBufferID = Graphics::Utils::BufferManager::GenerateBuffer
                (
                    Graphics::Utils::BufferType::IndexBuffer,
                    renderable.m_IndexSize * sizeof(uint32_t),
                    renderable.m_Indices
                );

                chunk.m_IsDirty = false;
            }
        }

        const char* GetName() override { return "VoxelTErrainSystem"; }
    };
}
