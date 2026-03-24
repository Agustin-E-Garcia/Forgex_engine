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

                renderable.m_MeshAsset = GET_SERVICE(Assets::AssetManager)->CreateRuntimeAsset<Graphics::MeshAsset>
                (
                    "ChunkMesh",
                    vertices.data(),
                    vertices.size(),
                    indices.data(),
                    indices.size()
                );

                chunk.m_IsDirty = false;
            }
        }

        const char* GetName() override { return "VoxelTErrainSystem"; }
    };
}
