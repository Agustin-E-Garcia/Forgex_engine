#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>
#include <ForgexFiles.h>
#include <algorithm>

#include "../Components/Chunk.h"
#include "../Utils/ChunkMesher.h"

namespace Forgex::Voxel::Systems
{
    class VoxelTerrainSystem : public Core::Interfaces::PerEntitySystem<Components::Chunk, Graphics::Components::Renderable>
    {
    public:
        void OnUpdate(float deltaTime, const entt::entity& entity, Components::Chunk& chunk, Graphics::Components::Renderable& renderable) override
        {
            if(chunk.m_DensityFuture.valid() && chunk.m_DensityFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                chunk.m_Data = chunk.m_DensityFuture.get();
                chunk.m_IsDirty = true;
            }

            if(!chunk.m_IsDirty) return;

            if(!chunk.m_MeshingFuture.valid())
            {
                chunk.m_MeshingFuture = GET_SERVICE(Core::JobManager)->Enqueue<Graphics::MeshData>([this, data = chunk.m_Data]() { return MeshChunk(data); });
                return;
            }

            if(chunk.m_MeshingFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                Graphics::MeshData mesh = chunk.m_MeshingFuture.get();

                renderable.m_MeshAsset = GET_SERVICE(Assets::AssetManager)->CreateRuntimeAsset<Graphics::MeshAsset>
                (
                    "ChunkMesh",
                    mesh.m_Vertices.data(),
                    mesh.m_Vertices.size(),
                    mesh.m_Indices.data(),
                    mesh.m_Indices.size()
                );

                chunk.m_IsDirty = false;
            }
        }

        Graphics::MeshData MeshChunk(const Components::ChunkData chunk)
        {
            Utils::ChunkMesher mesher = Utils::ChunkMesher(chunk);

            Graphics::MeshData data;
            mesher.GenerateMesh(data.m_Vertices, data.m_Indices);

            return data;
        }

        const char* GetName() override { return "VoxelTerrainSystem"; }
    };
}
