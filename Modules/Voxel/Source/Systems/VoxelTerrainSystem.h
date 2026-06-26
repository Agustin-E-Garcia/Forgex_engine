#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>
#include <ForgexFiles.h>

#include "../Components/Chunk.h"
#include "../Utils/ChunkMesher.h"

#include <algorithm>
#include <cstdint>
#include <vector>

namespace Forgex::Voxel::Systems
{
    class VoxelTerrainSystem : public Core::Interfaces::ISystem
    {
    public:
        void Update(entt::registry& registry, float deltaTime) override
        {
            auto view_chunk = registry.view<Components::Chunk, Core::Components::Transform>();

            for(auto&& [entity, chunk, Transform] : view_chunk.each())
            {
                if(chunk.m_DensityFuture.valid() && chunk.m_DensityFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
                {
                    chunk.m_Data = chunk.m_DensityFuture.get();
                    chunk.m_IsDirty = true;
                }

                if(!chunk.m_IsDirty) continue;

                if(!chunk.m_MeshingFuture.valid())
                {
                    const std::vector<int8_t>& densities = chunk.m_Data.m_DensityValues;
                    bool fullAir   = std::all_of(densities.begin(), densities.end(), [](int8_t v){ return v == 0; });
                    bool fullSolid = std::all_of(densities.begin(), densities.end(), [](int8_t v){ return v == (int8_t)255; });
                    if(fullAir || fullSolid)
                    {
                        chunk.m_IsDirty = false;
                        continue;
                    }

                    chunk.m_MeshingFuture = GET_SERVICE(Core::JobManager)->Enqueue<Graphics::MeshData>([this, data = chunk.m_Data]() { return MeshChunk(data); });
                    continue;
                }

                if(chunk.m_MeshingFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
                {
                    Graphics::Components::Renderable& renderable = registry.emplace<Graphics::Components::Renderable>(entity);
                    renderable.m_MaterialAsset = GET_SERVICE(Assets::AssetManager)->LoadAsset<Graphics::MaterialAsset>("Resources/Materials/Terrain.FMaterial");

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
