#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>
#include <ForgexAssets.h>
#include <cstdint>

#include "../Components/VoxelMap.h"
#include "../Utils/TerrainGenerator.h"

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
            for(int y = 0; y < chunks.y; y++)
            for(int x = 0; x < chunks.x; x++)
            {
                entt::entity ent = registry.create();
                Graphics::Components::Renderable& renderable = registry.emplace<Graphics::Components::Renderable>(ent);

                Components::Chunk& chunk = registry.emplace<Components::Chunk>(ent);
                chunk.m_Position = glm::vec3(x, y, z);
                chunk.m_Size = map.m_ChunkSize;
                chunk.m_SampleDensity = map.m_SampleDensity;
                chunk.m_Cutoff = map.m_Cutoff;

                renderable.m_ModelMatrix = glm::translate(glm::mat4(1.0f), (chunk.m_Position * chunk.m_Size));

                chunk.m_Samples = (chunk.m_Size / glm::vec3(chunk.m_SampleDensity)) + glm::vec3(1.0f);
                chunk.m_DensityValues.resize((int)chunk.m_Samples.x * (int)chunk.m_Samples.y * (int)chunk.m_Samples.z, 255);

                renderable.m_MaterialAsset = GET_SERVICE(Assets::AssetManager)->LoadAsset<Graphics::MaterialAsset>("Resources/Materials/Lit.FMaterial");

                chunk.m_DensityFuture = GET_SERVICE(Core::JobManager)->Enqueue<std::vector<uint8_t>>([this, &chunk]() { return SetupChunk(chunk); });

                map.m_Chunks.push_back(&chunk);
            }
        }

        std::vector<uint8_t> SetupChunk(Components::Chunk& chunk)
        {
            Utils::TerrainGenerator generator = Utils::TerrainGenerator(chunk.m_NoiseSeed);

            std::vector<uint8_t> densityValues;
            densityValues.resize((int)chunk.m_Samples.x * (int)chunk.m_Samples.y * (int)chunk.m_Samples.z, 255);

            glm::vec3 worldOffset = chunk.m_Position * chunk.m_Size;
            for(int i = 0; i < chunk.m_DensityValues.size(); i++)
            {
                glm::vec3 worldPosition = worldOffset + GetSamplePosition(chunk, i);
                float surfaceHeight;
                densityValues[i] = generator.GetDensityValueAtPoint(worldPosition, chunk.m_Size.y, &surfaceHeight);
            }

            return densityValues;
        }

        glm::vec3 GetSamplePosition(Components::Chunk& chunk, int sampleID)
        {
            int x = sampleID % chunk.m_Samples.x;
            int y = (sampleID / chunk.m_Samples.x) % chunk.m_Samples.y;
            int z = sampleID / (chunk.m_Samples.x * chunk.m_Samples.y);

            return glm::vec3(x, y, z) * chunk.m_SampleDensity;
        }
 
        const char* GetName() override { return "VoxelMapSetupSystem"; }
    };
}
