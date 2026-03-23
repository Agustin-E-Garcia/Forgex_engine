#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>
#include <ForgexAssets.h>

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

                SetupChunk(chunk, renderable);

                map.m_Chunks.push_back(&chunk);
            }
        }

        void SetupChunk(Components::Chunk& chunk, Graphics::Components::Renderable& renderable)
        {
            renderable.m_ModelMatrix = glm::translate(glm::mat4(1.0f), (chunk.m_Position * chunk.m_Size));

            Utils::TerrainGenerator generator = Utils::TerrainGenerator(chunk.m_NoiseSeed);

            chunk.m_Samples = (chunk.m_Size / glm::vec3(chunk.m_SampleDensity)) + glm::vec3(1.0f);
            int totalSamples = (int)chunk.m_Samples.x * (int)chunk.m_Samples.y * (int)chunk.m_Samples.z;
            chunk.m_DensityValues.resize(totalSamples, 255);

            glm::vec3 worldOffset = chunk.m_Position * chunk.m_Size;
            for(int i = 0; i < chunk.m_DensityValues.size(); i++)
            {
                glm::vec3 worldPosition = worldOffset + GetSamplePosition(chunk, i);
                float surfaceHeight;
                chunk.m_DensityValues[i] = generator.GetDensityValueAtPoint(worldPosition, chunk.m_Size.y, &surfaceHeight);
            }

            chunk.m_IsDirty = true;

            renderable.m_ShaderAsset = GET_SERVICE(Assets::AssetManager)->LoadAsset<Graphics::ShaderAsset>("Resources/Shaders/ColorShader.FShader");
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
