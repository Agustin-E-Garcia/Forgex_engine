#include "Chunk.h"
#include "Renderer.h"
#include "GL/glew.h"

const int Chunk::s_ChunkSize = 16;

Chunk::Chunk()
{
	m_Voxels.reserve(std::pow(s_ChunkSize, 3));
	
	for (int i = 0; i < m_Voxels.capacity(); i++)
	{
		m_Voxels.push_back(new Voxel());
	}

    GenerateVertices();
}

Chunk::~Chunk() 
{
    for (int i = m_Voxels.size() - 1; i >= 0; i--)
    {
        delete m_Voxels[i];
    }
}

DrawInfo Chunk::GetDrawInfo()
{
	DrawInfo info{};
	info.vertexBufferID = m_VertexBufferID;
    info.uvBufferID = m_UVBufferID;
	info.modelMatrix = glm::mat4(1.0f);
    info.indexCount = m_Vertices.size();
	return info;
}

int Chunk::FlattenIndex(int x, int y, int z)
{
    return (y * s_ChunkSize * s_ChunkSize) + (z * s_ChunkSize) + x;
}

void Chunk::GenerateVertices() 
{
	m_Vertices.clear();

	for (int y = 0; y < s_ChunkSize; y++)
	{
		for (int z = 0; z < s_ChunkSize; z++)
		{
            for (int x = 0; x < s_ChunkSize; x++)
            {
                if (!m_Voxels[FlattenIndex(x, y ,z)]->IsActive()) continue; // if voxel is not active, we don't render it

                // Render Front triangles only if they are visible
                if (z + 1 >= s_ChunkSize || !m_Voxels[FlattenIndex(x, y, z + 1)]->IsActive())
                {
                    PushVertex(-0.5f + x, 0.5f + y, 0.5f + z);
                    PushVertex(-0.5f + x, -0.5f + y, 0.5f + z);
                    PushVertex(0.5f + x, -0.5f + y, 0.5f + z);

                    PushVertex(0.5f + x, 0.5f + y, 0.5f + z);
                    PushVertex(-0.5f + x, 0.5f + y, 0.5f + z);
                    PushVertex(0.5f + x, -0.5f + y, 0.5f + z);
                }

                // Render Back triangles only if they are visible
                if (z - 1 < 0 || !m_Voxels[FlattenIndex(x, y, z - 1)]->IsActive())
                {
                    PushVertex(0.5f + x, 0.5f + y, -0.5f + z);
                    PushVertex(-0.5f + x, -0.5f + y, -0.5f + z);
                    PushVertex(-0.5f + x, 0.5f + y, -0.5f + z);

                    PushVertex(0.5f + x, 0.5f + y, -0.5f + z);
                    PushVertex(0.5f + x, -0.5f + y, -0.5f + z);
                    PushVertex(-0.5f + x, -0.5f + y, -0.5f + z);
                }

                // Render Top triangles only if they are visible
                if (y + 1 >= s_ChunkSize || !m_Voxels[FlattenIndex(x, y + 1, z)]->IsActive())
                {
                    PushVertex(0.5f + x, 0.5f + y, 0.5f + z);
                    PushVertex(0.5f + x, 0.5f + y, -0.5f + z);
                    PushVertex(-0.5f + x, 0.5f + y, -0.5f + z);

                    PushVertex(0.5f + x, 0.5f + y, 0.5f + z);
                    PushVertex(-0.5f + x, 0.5f + y, -0.5f + z);
                    PushVertex(-0.5f + x, 0.5f + y, 0.5f + z);
                }

                // Render Bottom triangles only if they are visible
                if (y - 1 < 0 || !m_Voxels[FlattenIndex(x, y - 1, z)]->IsActive())
                {
                    PushVertex(0.5f + x, -0.5f + y, 0.5f + z);
                    PushVertex(-0.5f + x, -0.5f + y, -0.5f + z);
                    PushVertex(0.5f + x, -0.5f + y, -0.5f + z);

                    PushVertex(0.5f + x, -0.5f + y, 0.5f + z);
                    PushVertex(-0.5f + x, -0.5f + y, 0.5f + z);
                    PushVertex(-0.5f + x, -0.5f + y, -0.5f + z);
                }

                // Render Right triangles only if they are visible
                if (x + 1 >= s_ChunkSize || !m_Voxels[FlattenIndex(x + 1, y, z)]->IsActive())
                {
                    PushVertex(0.5f + x, 0.5f + y, 0.5f + z);
                    PushVertex(0.5f + x, -0.5f + y, -0.5f + z);
                    PushVertex(0.5f + x, 0.5f + y, -0.5f + z);

                    PushVertex(0.5f + x, -0.5f + y, -0.5f + z);
                    PushVertex(0.5f + x, 0.5f + y, 0.5f + z);
                    PushVertex(0.5f + x, -0.5f + y, 0.5f + z);
                }

                // Render Back triangles only if they are visible
                if (x - 1 < 0 || !m_Voxels[FlattenIndex(x - 1, y, z)]->IsActive())
                {
                    PushVertex(-0.5f + x, -0.5f + y, -0.5f + z);
                    PushVertex(-0.5f + x, -0.5f + y, 0.5f + z);
                    PushVertex(-0.5f + x, 0.5f + y, 0.5f + z);

                    PushVertex(-0.5f + x, -0.5f + y, -0.5f + z);
                    PushVertex(-0.5f + x, 0.5f + y, 0.5f + z);
                    PushVertex(-0.5f + x, 0.5f + y, -0.5f + z);
                }
			}
		}
	}

    GenerateBuffers();
}

void Chunk::PushVertex(float x, float y, float z) 
{
    m_Vertices.push_back(x);
    m_Vertices.push_back(y);
    m_Vertices.push_back(z);
}

void Chunk::GenerateBuffers()
{
	Renderer::DeleteBuffer(m_VertexBufferID);
	m_VertexBufferID = Renderer::GenerateBuffer(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data());
    m_UVBufferID = Renderer::GenerateBuffer(GL_ARRAY_BUFFER, m_UVs.size() * sizeof(float), m_UVs.data());
}

Voxel* Chunk::GetVoxel(int x, int y, int z) 
{
	return nullptr;
}