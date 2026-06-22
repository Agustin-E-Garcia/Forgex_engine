#include "WormCaveStep.h"
#include "../../Components/VoxelChunk.h"
#include "glm/geometric.hpp"

#include <random>
#include <utility>

namespace Forgex::Voxel::Utils::TerrainSteps
{
    WormCaveStep::WormCaveStep(glm::vec3 mapArea)
    {
        // Build a handful of "worms": each worm starts at an underground point and
        // takes a series of steps in a slowly-wandering direction, dropping a node
        // (a sphere) at every step. Execute() later carves the union of those spheres,
        // so overlapping consecutive nodes read as a continuous winding tunnel.

        constexpr int wormCount = 10;
        constexpr int stepsPerWorm = 10;
        constexpr float minRadius = 10.0f;
        constexpr float maxRadius = 15.0f;
        constexpr float stepLength = 10.0f; // distance between consecutive nodes; < radius keeps spheres overlapping
        constexpr float wander = 0.5f;      // how sharply the direction can turn each step

        // The world is centered on the origin, so it spans [-half, +half] per axis.
        glm::vec3 halfArea = mapArea * 0.5f;

        // Keep start points away from the edges so the path has room to travel, and
        // below the surface (terrain lives in y <= 0) so worms begin in solid rock.
        glm::vec3 maxOffset = glm::max(halfArea - maxRadius, glm::vec3(0.0f));

        // Fixed seed keeps cave placement deterministic between runs.
        std::mt19937 rng(23523);
        std::uniform_real_distribution<float> radiusDist(minRadius, maxRadius);
        std::uniform_real_distribution<float> dirDist(-1.0f, 1.0f);
        std::uniform_real_distribution<float> xDist(-maxOffset.x, maxOffset.x);
        std::uniform_real_distribution<float> yDist(-maxOffset.y, glm::min(-maxRadius, maxOffset.y));
        std::uniform_real_distribution<float> zDist(-maxOffset.z, maxOffset.z);

        m_WormPath.reserve(wormCount);
        for(int i = 0; i < wormCount; i++)
        {
            glm::vec3 position(xDist(rng), yDist(rng), zDist(rng));
            glm::vec3 direction = glm::normalize(glm::vec3(dirDist(rng), dirDist(rng), dirDist(rng)));

            std::vector<WormPathNode> path;
            path.reserve(stepsPerWorm);
            for(int step = 0; step < stepsPerWorm; step++)
            {
                WormPathNode node;
                node.m_WorldPosition = position;
                node.m_Radius = radiusDist(rng);
                path.push_back(node);

                // Nudge the heading a little, then advance so the tunnel curves rather
                // than running dead straight.
                direction = glm::normalize(direction + glm::vec3(dirDist(rng), dirDist(rng), dirDist(rng)) * wander);
                position += direction * stepLength;
            }

            m_WormPath.push_back(std::move(path));
        }
    }

    bool SphereIntersectsAABB(glm::vec3 center, float radius, glm::vec3 chunkMin, glm::vec3 chunkMax)
    {
        glm::vec3 closest = glm::clamp(center, chunkMin, chunkMax);
        float distSq = glm::dot(closest - center, closest - center);
        return distSq <= (radius * radius);
    }

    uint64_t GetSampleID(glm::vec3 position, const Components::Chunk& chunk)
    {
        return position.y + (position.x * chunk.m_Samples.y) + (position.z * chunk.m_Samples.y * chunk.m_Samples.x);
    }

    void WormCaveStep::Execute(Components::Chunk& chunk)
    {
        // Iterate over the cave paths, check if they affect this Chunk
        // Figure out which density points should be modified and do so to make the cave

        // m_Position is a chunk-grid coordinate; the world offset is position * size
        // (matches SurfaceNoiseStep). Build the chunk AABB in world space.
        glm::vec3 worldOffset = chunk.m_Position * chunk.m_Size;
        glm::vec3 chunkMin = worldOffset;
        glm::vec3 chunkMax = worldOffset + chunk.m_Size;

        for(std::vector<WormPathNode> path : m_WormPath)
        for(WormPathNode node : path)
        {
            // figure out if the cavern should modify this chunk
            if(SphereIntersectsAABB(node.m_WorldPosition, node.m_Radius, chunkMin, chunkMax))
            {
                for(int z = 0; z < chunk.m_Samples.z; z++)
                for(int y = 0; y < chunk.m_Samples.y; y++)
                for(int x = 0; x < chunk.m_Samples.x; x++)
                {
                    glm::vec3 worldPosition = worldOffset + glm::vec3(x, y, z) * chunk.m_SampleDensity;
                    float distance = glm::length(worldPosition - node.m_WorldPosition);

                    if(distance < node.m_Radius)
                    {
                        float t = 1.0f - (distance / node.m_Radius);

                        // Carve toward air. Clamp into the int8_t range *before* storing:
                        // air is already pinned at -128, so an unclamped subtraction
                        // underflows and wraps back up to a solid value, leaving thin
                        // spherical shells ("flying cave walls") around caverns in open air.
                        uint64_t sampleID = GetSampleID(glm::vec3(x, y, z), chunk);
                        int carved = chunk.m_DensityValues[sampleID] - static_cast<int>(127 * t);
                        chunk.m_DensityValues[sampleID] = static_cast<int8_t>(glm::clamp(carved, -128, 127));
                    }
                }
            }
        }
   }
}
