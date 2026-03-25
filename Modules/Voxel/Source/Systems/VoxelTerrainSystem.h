#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>

#include "../Components/VoxelChunk.h"
#include "../Utils/TerrainGenerator.h"
#include "../Utils/ChunkMesher.h"

#include <ForgexAssets.h>

namespace Forgex::Voxel::Systems
{
    class VoxelTerrainSystem : public Core::Interfaces::PerEntitySystem<Components::Chunk, Graphics::Components::Renderable>
    {
    public:
        void OnUpdate(float deltaTime, const entt::entity& entity, Components::Chunk& chunk, Graphics::Components::Renderable& renderable) override
        {
            if(chunk.m_DensityFuture.valid() && chunk.m_DensityFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                chunk.m_DensityValues = std::move(chunk.m_DensityFuture.get());
                chunk.m_IsDirty = true;
            }

            if(!chunk.m_IsDirty) return;

            if(!chunk.m_MeshingFuture.valid())
            {
                chunk.m_MeshingFuture = GET_SERVICE(Core::JobManager)->Enqueue<Assets::Files::MeshData>([this, &chunk]() { return MeshChunk(chunk); });
                return;
            }

            if(chunk.m_MeshingFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                Assets::Files::MeshData mesh = chunk.m_MeshingFuture.get();

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

        Assets::Files::MeshData MeshChunk(const Components::Chunk& chunk)
        {
            Utils::TerrainGenerator generator = Utils::TerrainGenerator(chunk.m_NoiseSeed);
            Utils::ChunkMesher mesher = Utils::ChunkMesher(&chunk, &generator);

            Assets::Files::MeshData data;
            mesher.GenerateMesh(data.m_Vertices, data.m_Indices);

            return data;
        }

        const char* GetName() override { return "VoxelTErrainSystem"; }
    };
}
