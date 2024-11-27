#include "Chunk.h"
#include "ChunkManager.h"
#include "../../Log.h"
#include "../../Utils/NoiseGenerator.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>
#include <algorithm>

static int s_SubchunkSize = 32;

static int s_ChunkMeshingKey = -1;
static int s_SubchunkMeshingKey = -1;

Chunk::Chunk(glm::vec3 chunkPosition) : m_ChunkPosition(chunkPosition)
{
    m_SubChunks.resize(255 / s_SubchunkSize);
}

Chunk::~Chunk() 
{
}

bool Chunk::TryMeshChunk(std::vector<const Chunk*> adjacentChunks, bool forceMeshing)
{
    if (IsMeshed() && !forceMeshing) return true;

    for (int i = 0; i < adjacentChunks.size(); i++)
    {
        if (!adjacentChunks[i]) continue;
        if (!adjacentChunks[i]->IsLoaded()) return false;
    }
    
    BuildMesh(adjacentChunks);
    UpdateDrawInfo();

    return true;
}

void Chunk::ChangePosition(glm::vec3 newPosition)
{
    m_ChunkPosition = newPosition;

    for (int i = 0; i < m_SubChunks.size(); i++)
    {
        m_SubChunks[i].m_IsLoaded = false;
        m_SubChunks[i].m_IsMeshed = false;
    }
}

void Chunk::RequestMeshUpdate()
{
    for (int i = 0; i < m_SubChunks.size(); i++)
    {
        m_SubChunks[i].m_IsMeshed = false;
    }
}

void Chunk::BuildMesh(std::vector<const Chunk*> adjacentChunks)
{
    // adjacentChunks:
    // [0] right
    // [1] left
    // [2] front
    // [3] back

    for (int i = 0; i < m_SubChunks.size(); i++)
    {
        if (m_SubChunks[i].m_IsMeshed) continue;

        std::vector<uint32_t> top = (i + 1) < m_SubChunks.size() ? m_SubChunks[i + 1].m_BinaryMap : std::vector<uint32_t>(std::pow(s_SubchunkSize, 2));
        std::vector<uint32_t> bottom = (i - 1) >= 0 ? m_SubChunks[i - 1].m_BinaryMap : std::vector<uint32_t>(std::pow(s_SubchunkSize, 2));
        std::vector<uint32_t> right = adjacentChunks[0] ? adjacentChunks.at(0)->GetSubchunk(i)->m_BinaryMap : std::vector<uint32_t>();
        std::vector<uint32_t> left  = adjacentChunks[1] ? adjacentChunks.at(1)->GetSubchunk(i)->m_BinaryMap : std::vector<uint32_t>();
        std::vector<uint32_t> front = adjacentChunks[2] ? adjacentChunks.at(2)->GetSubchunk(i)->m_BinaryMap : std::vector<uint32_t>();
        std::vector<uint32_t> back  = adjacentChunks[3] ? adjacentChunks.at(3)->GetSubchunk(i)->m_BinaryMap : std::vector<uint32_t>();

        m_SubChunks[i].BinaryMeshing(i, top, bottom, right, left, front, back);
    }
}

void Chunk::LoadChunk()
{
    std::vector<uint8_t> heightMap;
    std::vector<float> noiseMap = NoiseGenerator::GenerateNoiseMap(m_ChunkPosition.x * s_SubchunkSize, (m_ChunkPosition.x + 1) * s_SubchunkSize, m_ChunkPosition.z * s_SubchunkSize, (m_ChunkPosition.z + 1) * s_SubchunkSize, 300.0f, 4, 0.5f, 2.0f);

    for (int z = 0; z < s_SubchunkSize; z++)
    {
        for (int x = 0; x < s_SubchunkSize; x++)
        {
            int height = std::floor(40.0f + noiseMap[x + (z * s_SubchunkSize)] * 15.0f);
            heightMap.push_back(std::min(height, 220));
        }
    }

    for (int i = 0; i < m_SubChunks.size(); i++)
    {
        m_SubChunks[i].LoadSubchunk(i, heightMap);
    }
}

bool Chunk::IsLoaded() const
{
    for (int i = 0; i < m_SubChunks.size(); i++)
    {
        if (!m_SubChunks[i].m_IsLoaded) return false;
    }

    return true;
}

bool Chunk::IsMeshed() const
{
    for (int i = 0; i < m_SubChunks.size(); i++)
    {
        if (!m_SubChunks[i].m_IsMeshed) return false;
    }

    return true;
}

void Chunk::UpdateDrawInfo()
{
    std::vector<uint32_t> vertices;
    for (int i = 0; i < m_SubChunks.size(); i++)
    {
        m_SubChunks[i].CopyVertices(&vertices);
    }

    Renderer::DeleteBuffer(m_DrawInfo.vertexBufferID);
    m_DrawInfo.vertexBufferID = Renderer::GenerateVertexBuffer(vertices.size() * sizeof(uint32_t), vertices.data());
    m_DrawInfo.modelMatrix = glm::translate(glm::mat4(1.0f), m_ChunkPosition * glm::vec3(s_SubchunkSize));
    m_DrawInfo.indexCount = vertices.size();
}

/* ============================= SUBCHUNK =================================== */

Subchunk::Subchunk() : m_IsLoaded(false), m_IsMeshed(false)
{
    m_Voxels.resize(std::pow(s_SubchunkSize, 3));
    m_BinaryMap.resize(std::pow(s_SubchunkSize, 2));
}

Subchunk::~Subchunk() {}

int Subchunk::FlattenIndex(int x, int y, int z) 
{
    return (y * s_SubchunkSize * s_SubchunkSize) + (z * s_SubchunkSize) + x;
}

int Subchunk::FlattenIndex(int x, int z)
{
    return x + (z * s_SubchunkSize);
}

uint32_t Subchunk::GetBinaryMap(int x, int z)
{
    if (x < 0 || x >= s_SubchunkSize || z < 0 || z >= s_SubchunkSize) return 0;

    int index = FlattenIndex(x, z);
    return index < m_BinaryMap.size() && index >= 0 ? m_BinaryMap[index] : 0;
}

void Subchunk::LoadSubchunk(int subChunkIndex, std::vector<uint8_t> chunkHeightMap)
{
    int subchunkMin = s_SubchunkSize * subChunkIndex;
    int subchunkMax = s_SubchunkSize * (subChunkIndex + 1);

    std::fill(m_BinaryMap.begin(), m_BinaryMap.end(), UINT32_MAX);

    for (int i = 0; i < m_BinaryMap.size(); i++)
    {
        if (chunkHeightMap[i] > subchunkMax) continue;

        if (chunkHeightMap[i] < subchunkMin) m_BinaryMap[i] = 0;
        else
        {
            for (int y = 0; y < s_SubchunkSize; y++)
            {
                int voxelPoisition = y + subchunkMin;
                if (voxelPoisition > chunkHeightMap[i]) m_BinaryMap[i] &= ~(1 << y);
            }
        }
    }

    m_IsLoaded = true;
}

void Subchunk::BinaryMeshing(int subChunkIndex, std::vector<uint32_t> top, std::vector<uint32_t> bottom, std::vector<uint32_t> right, std::vector<uint32_t> left, std::vector<uint32_t> front, std::vector<uint32_t> back)
{
    m_Vertices.clear();

    int subchunkPosition = subChunkIndex * s_SubchunkSize;

    for (int z = 0; z < s_SubchunkSize; z++)
    {
        for (int x = 0; x < s_SubchunkSize; x++)
        {
            uint32_t column = GetBinaryMap(x, z);

            if (column == 0) continue;

            uint32_t topMask = ((~(column >> 1)) & column) & ~((top[FlattenIndex(x, z)] & 1) << 31);
            uint32_t bottomMask = ((~(column << 1)) & column) & ~(bottom[FlattenIndex(x, z)] >> 31);
            uint32_t rightMask = ~GetBinaryMap(x - 1, z) & column;
            uint32_t leftMask = ~GetBinaryMap(x + 1, z) & column;
            uint32_t frontMask = ~GetBinaryMap(x, z + 1) & column;
            uint32_t backMask = ~GetBinaryMap(x, z - 1) & column;

            if (x + 1 >= s_SubchunkSize && !left.empty()) leftMask &= ~(left[FlattenIndex(0, z)]);
            if (x - 1 <= 0 && !right.empty()) rightMask &= ~(right[FlattenIndex(s_SubchunkSize - 1, z)]);
            
            if (z + 1 >= s_SubchunkSize && !front.empty()) frontMask &= ~(front[FlattenIndex(x, 0)]);
            if (z - 1 <= 0 && !back.empty()) backMask &= ~(back[FlattenIndex(x, s_SubchunkSize - 1)]);

            uint32_t fullmask = topMask | bottomMask | rightMask | leftMask | frontMask | backMask;

            if (fullmask == 0) continue;

            for (int y = 0; y < s_SubchunkSize; y++)
            {
                if ((fullmask >> y & 1) == 0) continue;

                int voxelIndex = FlattenIndex(x, y, z);
                uint8_t voxelType = m_Voxels[voxelIndex].GetType();

                int aux = topMask << y;

                if ((topMask >> y) & 1)
                {
                    PushVertexData(0 + x, 1 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(1 + x, 1 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(1 + x, 1 + y + subchunkPosition, 0 + z, voxelType);

                    PushVertexData(1 + x, 1 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(0 + x, 1 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(0 + x, 1 + y + subchunkPosition, 1 + z, voxelType);
                }

                if ((bottomMask << y) & 1)
                {
                    PushVertexData(0 + x, 0 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(1 + x, 0 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(1 + x, 0 + y + subchunkPosition, 1 + z, voxelType);

                    PushVertexData(1 + x, 0 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(0 + x, 0 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(0 + x, 0 + y + subchunkPosition, 0 + z, voxelType);
                }

                if ((rightMask >> y) & 1) 
                {
                    PushVertexData(0 + x, 0 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(0 + x, 0 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(0 + x, 1 + y + subchunkPosition, 1 + z, voxelType);

                    PushVertexData(0 + x, 1 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(0 + x, 1 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(0 + x, 0 + y + subchunkPosition, 0 + z, voxelType);
                }

                if ((leftMask >> y) & 1)
                {
                    PushVertexData(1 + x, 0 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(1 + x, 0 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(1 + x, 1 + y + subchunkPosition, 0 + z, voxelType);

                    PushVertexData(1 + x, 1 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(1 + x, 1 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(1 + x, 0 + y + subchunkPosition, 1 + z, voxelType);
                }

                if ((frontMask >> y) & 1) 
                {
                    PushVertexData(0 + x, 0 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(1 + x, 0 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(1 + x, 1 + y + subchunkPosition, 1 + z, voxelType);

                    PushVertexData(1 + x, 1 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(0 + x, 1 + y + subchunkPosition, 1 + z, voxelType);
                    PushVertexData(0 + x, 0 + y + subchunkPosition, 1 + z, voxelType);
                }

                if ((backMask >> y) & 1) 
                {
                    PushVertexData(1 + x, 0 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(0 + x, 0 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(0 + x, 1 + y + subchunkPosition, 0 + z, voxelType);

                    PushVertexData(0 + x, 1 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(1 + x, 1 + y + subchunkPosition, 0 + z, voxelType);
                    PushVertexData(1 + x, 0 + y + subchunkPosition, 0 + z, voxelType);
                }
            }
        }
    }

    m_IsMeshed = true;
}

void Subchunk::PushVertexData(uint8_t x, uint8_t y, uint8_t z, uint8_t blockType)
{
    // First we pack the values into a 32-bit integer
    uint32_t packedValue = (static_cast<uint32_t>(x) << 24) | (static_cast<uint32_t>(y) << 16) | (static_cast<uint32_t>(z) << 8) | (static_cast<uint32_t>(blockType));
    m_Vertices.emplace_back(packedValue);
}

void Subchunk::CopyVertices(std::vector<uint32_t>* vertices) 
{
    if (m_Vertices.empty()) return;

    vertices->insert(vertices->end(), m_Vertices.begin(), m_Vertices.end());
}