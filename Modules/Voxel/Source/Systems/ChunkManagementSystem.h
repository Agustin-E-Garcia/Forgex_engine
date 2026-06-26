#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>
#include <ForgexAssets.h>

#include "../Components/ChunkManager.h"
#include "../VoxelSettings.h"
#include "glm/geometric.hpp"

namespace Forgex::Voxel::Systems
{
    class ChunkManagementSystem : public Core::Interfaces::ISystem
    {
    public:
        void Update(entt::registry& registry, float deltaTime) override
        {
            auto view = registry.view<Components::ChunkManager>();
            for (entt::entity entity : view)
            {
                Components::ChunkManager& manager = view.get<Components::ChunkManager>(entity);
                Core::Components::Transform* centerTransform = registry.try_get<Core::Components::Transform>(manager.m_CenterEntity);

                if(centerTransform == nullptr) continue;

                const VoxelSettings* settings = GET_SERVICE(Core::Settings::ProjectSettings)->GetSettings<VoxelSettings>();
                glm::vec3 chunkSize = settings->GetChunkSampleCount() * settings->GetChunkSampleDensity();

                glm::vec3 centerChunk = glm::floor(centerTransform->m_Position / chunkSize);
                int range = manager.m_ViewRange;

                if(centerChunk == manager.m_LastFrameCenterPosition) continue;

                manager.m_LastFrameCenterPosition = centerChunk;

                for (auto it = manager.m_ChunkEntityCollection.begin(); it != manager.m_ChunkEntityCollection.end();)
                {
                    glm::vec3 distance = it->first - centerChunk;
                    if(glm::length(distance) <= (float)range)
                    {
                        ++it;
                        continue;
                    }

                    registry.destroy(it->second);
                    it = manager.m_ChunkEntityCollection.erase(it);
                }

                for (int z = -range; z <= range; z++)
                for (int y = -range * 0.5f; y <= range * 0.5f; y++)
                for (int x = -range; x <= range; x++)
                {
                    glm::vec3 offset = glm::vec3(x, y, z);
                    if (glm::length(offset) > (float)range) continue;

                    glm::vec3 chunkPosition = centerChunk + offset;

                    if(manager.m_ChunkEntityCollection.contains(chunkPosition)) continue;

                    entt::entity entity = registry.create();

                    Core::Components::Transform& transform = registry.emplace<Core::Components::Transform>(entity);
                    transform.m_Position = chunkPosition * chunkSize;
                    transform.m_Dirty = true;

                    Components::Chunk& chunk = registry.emplace<Components::Chunk>(entity);
                    chunk.m_Data.m_MapPosition = chunkPosition;
                    glm::vec3 samples = settings->GetChunkSampleCount() + glm::vec3(2.0f);
                    chunk.m_Data.m_DensityValues.reserve((int)samples.x * (int)samples.y * (int)samples.z);


                    chunk.m_DensityFuture = GET_SERVICE(Core::JobManager)->Enqueue<Components::ChunkData>([this, data = chunk.m_Data]() mutable
                        {
                            GET_SERVICE(Core::Settings::ProjectSettings)->GetSettings<VoxelSettings>()->GetVoxelPipeline().Execute(data);
                            return data;
                        }
                    );

                    manager.m_ChunkEntityCollection[chunkPosition] = entity;
                }
            }
        }

       const char* GetName() override { return "VoxelMapSetupSystem"; }
    };
}
