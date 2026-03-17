#pragma once
#include <ForgexScene.h>
#include <ForgexGraphics.h>
#include <ForgexVoxel.h>

namespace Forgex::Core
{
    class ChunkMeshingSystem : public Scene::PerEntitySystem<Voxel::Chunk>
    {
    public:
        SYSTEM_NAME(ChunkMeshingSystem);
        SYSTEM_TYPE(UpdateSystem);

        void OnUpdate(float deltaTime, entt::entity entity, Voxel::Chunk& chunk) override
        {
            if(!chunk.m_Initialized)
            {
                chunk.m_ModelMatrix = glm::translate(glm::mat4(1.0f), (chunk.m_Position * chunk.m_Size));
                GenerateDensity(chunk);
                chunk.m_Initialized = true;
            }

            if(!chunk.m_IsMeshed && chunk.m_IsDirty)
            {
                Voxel::TerrainGenerator generator = Voxel::TerrainGenerator(chunk.m_NoiseSeed);
                Voxel::ChunkMesher mesher = Voxel::ChunkMesher(&chunk, &generator);

                mesher.GenerateMesh();

                chunk.vertexBufferID = Graphics::Utils::BufferManager::GenerateBuffer
                (
                    Graphics::Utils::BufferType::VertexBuffer,
                    chunk.m_Vertices.size() * sizeof(float),
                    chunk.m_Vertices.data()
                );

                chunk.indexBufferID = Graphics::Utils::BufferManager::GenerateBuffer
                (
                    Graphics::Utils::BufferType::IndexBuffer,
                    chunk.m_Indices.size() * sizeof(uint32_t),
                    chunk.m_Indices.data()
                );

                chunk.m_IsDirty = false;
                chunk.m_IsMeshed = true;
            }
        }

        void GenerateDensity(Voxel::Chunk& chunk)
        {
            Voxel::TerrainGenerator generator = Voxel::TerrainGenerator(chunk.m_NoiseSeed);

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

            chunk.m_IsMeshed = false;
            chunk.m_IsDirty = true;
        }

        glm::vec3 GetSamplePosition(Voxel::Chunk& chunk, int sampleID)
        {
            int x = sampleID % chunk.m_Samples.x;
            int y = (sampleID / chunk.m_Samples.x) % chunk.m_Samples.y;
            int z = sampleID / (chunk.m_Samples.x * chunk.m_Samples.y);

            return glm::vec3(x, y, z) * chunk.m_SampleDensity;
        }
   };
}
