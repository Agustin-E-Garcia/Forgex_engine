#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>
#include <ForgexAssets.h>

#include "../Components/VoxelMap.h"
#include "../VoxelSettings.h"

#include "glm/fwd.hpp"

namespace Forgex::Voxel::Systems
{
    class VoxelMapSetupSystem : public Core::Interfaces::ISystem
    {
    public:
        void Setup(entt::registry &registry) override
        {
            entt::entity entity = registry.create();
            Components::VoxelMap& map = registry.emplace<Components::VoxelMap>(entity);

            glm::vec3 chunks = (map.m_MapArea / map.m_ChunkSize) * 0.5f;
            int chunkCount = chunks.x * chunks.y * chunks.z;
            map.m_Chunks.reserve(chunkCount);

            for(int z = -chunks.z; z < chunks.z; z++)
            for(int y = -chunks.y; y < chunks.y; y++)
            for(int x = -chunks.x; x < chunks.x; x++)
            {
                entt::entity ent = registry.create();
                Core::Components::Transform& transform = registry.emplace<Core::Components::Transform>(ent);
                Graphics::Components::Renderable& renderable = registry.emplace<Graphics::Components::Renderable>(ent);

                Components::Chunk& chunk = registry.emplace<Components::Chunk>(ent);
                chunk.m_Position = glm::vec3(x, y, z);
                chunk.m_Size = map.m_ChunkSize;
                chunk.m_SampleDensity = map.m_SampleDensity;
                chunk.m_Cutoff = map.m_Cutoff;
                chunk.m_NoiseSeed = map.m_Seed;

                transform.m_Position = glm::vec3(x, y, z) * map.m_ChunkSize;
                transform.m_Dirty = true;

                chunk.m_Samples = (chunk.m_Size / glm::vec3(chunk.m_SampleDensity)) + glm::vec3(2.0f);
                chunk.m_DensityValues.reserve((int)chunk.m_Samples.x * (int)chunk.m_Samples.y * (int)chunk.m_Samples.z);

                renderable.m_MaterialAsset = GET_SERVICE(Assets::AssetManager)->LoadAsset<Graphics::MaterialAsset>("Resources/Materials/Terrain.FMaterial");

                chunk.m_DensityFuture = GET_SERVICE(Core::JobManager)->Enqueue<void>([this, &chunk] 
                    {
                        return GET_SERVICE(Core::Settings::ProjectSettings)->GetSettings<VoxelSettings>()->GetVoxelPipeline().Execute(chunk);
                    }
                );

                map.m_Chunks.push_back(&chunk);
            }
        }

       const char* GetName() override { return "VoxelMapSetupSystem"; }
    };
}
