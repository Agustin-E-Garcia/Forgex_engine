#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>
#include <ForgexAssets.h>
#include <cstdint>

#include "../Components/VoxelMap.h"
#include "../Utils/TerrainGenerator.h"
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

            glm::vec3 chunks = map.m_MapArea / map.m_ChunkSize;
            int chunkCount = chunks.x * chunks.y * chunks.z;
            map.m_Chunks.reserve(chunkCount);

            for(int z = 0; z < chunks.z; z++)
            for(int y = -(chunks.y *0.5f); y < chunks.y * 0.5f; y++)
            for(int x = 0; x < chunks.x; x++)
            {
                entt::entity ent = registry.create();
                Core::Components::Transform& transform = registry.emplace<Core::Components::Transform>(ent);
                Graphics::Components::Renderable& renderable = registry.emplace<Graphics::Components::Renderable>(ent);

                Components::Chunk& chunk = registry.emplace<Components::Chunk>(ent);
                chunk.m_Position = glm::vec3(x, y, z);
                chunk.m_Size = map.m_ChunkSize;
                chunk.m_SampleDensity = map.m_SampleDensity;
                chunk.m_Cutoff = map.m_Cutoff;

                transform.m_Position = glm::vec3(x, y, z) * map.m_ChunkSize;
                transform.m_Dirty = true;

                chunk.m_Samples = (chunk.m_Size / glm::vec3(chunk.m_SampleDensity)) + glm::vec3(2.0f);
                chunk.m_DensityValues.reserve((int)chunk.m_Samples.x * (int)chunk.m_Samples.y * (int)chunk.m_Samples.z);

                renderable.m_MaterialAsset = GET_SERVICE(Assets::AssetManager)->LoadAsset<Graphics::MaterialAsset>("Resources/Materials/Terrain.FMaterial");

                //chunk.m_DensityFuture = GET_SERVICE(Core::JobManager)->Enqueue<std::vector<int8_t>>([this, &chunk]() { return SetupChunk(chunk); });

                {
                    PROFILE_FUNCTION("SetupChunk()");
                    SetupChunk(chunk);
                    chunk.m_IsDirty = true;
                }

                map.m_Chunks.push_back(&chunk);
            }
        }

        void SetupChunk(Components::Chunk& chunk)
        {
            Utils::TerrainGenerator generator = Utils::TerrainGenerator(chunk.m_NoiseSeed);

            glm::vec3 worldOffset = chunk.m_Position * chunk.m_Size;

            for(int z = 0; z < chunk.m_Samples.z; z++)
            for(int x = 0; x < chunk.m_Samples.x; x++)
            {
                float noiseValue = generator.GetNoiseAtXZ(worldOffset.x + x, worldOffset.z + z);

                for(int y = 0; y < chunk.m_Samples.y; y++)
                {
                    glm::vec3 worldPosition = worldOffset + glm::vec3(x, y, z);
                    chunk.m_DensityValues.push_back(generator.GetDensityValueAtPoint(worldPosition, 127, noiseValue));
                }
            }
        }

        const char* GetName() override { return "VoxelMapSetupSystem"; }
    };
}
