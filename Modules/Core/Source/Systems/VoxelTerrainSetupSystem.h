#pragma once
#include <ForgexScene.h>
#include <ForgexVoxel.h>
#include <format>
#include <glm/gtc/matrix_transform.hpp>

namespace Forgex::Core
{
    class VoxelTerrainSetupSystem : public Scene::ISystem
    {
    public:
        SYSTEM_NAME(VoxelTerrainSetupSystem);
        SYSTEM_TYPE(UpdateSystem)

        void Run(entt::registry& registry, float deltaTime) override
        {
            entt::entity entity = registry.create();
            registry.emplace<Scene::EntityInfo>(entity, "Voxel map");
            Voxel::VoxelMap& map = registry.emplace<Voxel::VoxelMap>(entity);

            glm::vec3 chunks = map.m_MapArea / map.m_ChunkSize;
            int chunkCount = chunks.x * chunks.y * chunks.z;
            map.m_Chunks.reserve(chunkCount);

            for(int z = 0; z < chunks.z; z++)
            for(int y = 0; y < chunks.y; y++)
            for(int x = 0; x < chunks.x; x++)
            {
                entt::entity ent = registry.create();
                registry.emplace<Scene::EntityInfo>(ent, std::format("Chunk [{0},{1},{2}]", x, y, z).c_str());
                Voxel::Chunk& chunk = registry.emplace<Voxel::Chunk>(ent);
                chunk.m_Position = glm::vec3(x, y, z);
                chunk.m_Size = map.m_ChunkSize;
                chunk.m_SampleDensity = map.m_SampleDensity;
                chunk.m_Cutoff = map.m_Cutoff;
            }
        }
    };
}
