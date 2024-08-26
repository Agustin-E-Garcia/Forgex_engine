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
}

DrawInfo Chunk::GetDrawInfo()
{
	DrawInfo info{};
	info.vertexBufferID = m_VertexBufferID;
	info.modelMatrix = glm::mat4(1.0f);
    info.indexCount = m_Vertices.size();
	return info;
}

void Chunk::GenerateVertices() 
{
	m_Vertices.clear();

    int i = 0;

	for (int y = 0; y < s_ChunkSize; y++)
	{
		for (int z = 0; z < s_ChunkSize; z++)
		{
            for (int x = 0; x < s_ChunkSize; x++)
            {
                if (!m_Voxels[i++]->IsActive()) continue;

                PushVertex( 0.0f + x, 0.0f + y, 0.0f + z);
                PushVertex( 0.0f + x, 0.0f + y, 1.0f + z);
                PushVertex( 0.0f + x, 1.0f + y, 1.0f + z);

                PushVertex( 1.0f + x, 1.0f + y, 0.0f + z);
                PushVertex( 0.0f + x, 0.0f + y, 0.0f + z);
                PushVertex( 0.0f + x, 1.0f + y, 0.0f + z);
                
                PushVertex( 1.0f + x, 0.0f + y, 1.0f + z);
                PushVertex( 0.0f + x, 0.0f + y, 0.0f + z);
                PushVertex( 1.0f + x, 0.0f + y, 0.0f + z);
                
                PushVertex( 1.0f + x, 1.0f + y, 0.0f + z);
                PushVertex( 1.0f + x, 0.0f + y, 0.0f + z);
                PushVertex( 0.0f + x, 0.0f + y, 0.0f + z);
                
                PushVertex( 0.0f + x, 0.0f + y, 0.0f + z);
                PushVertex( 0.0f + x, 1.0f + y, 1.0f + z);
                PushVertex( 0.0f + x, 1.0f + y, 0.0f + z);
                
                PushVertex( 1.0f + x, 0.0f + y, 1.0f + z);
                PushVertex( 0.0f + x, 0.0f + y, 1.0f + z);
                PushVertex( 0.0f + x, 0.0f + y, 0.0f + z);
                
                PushVertex( 0.0f + x, 1.0f + y, 1.0f + z);
                PushVertex( 0.0f + x, 0.0f + y, 1.0f + z);
                PushVertex( 1.0f + x, 0.0f + y, 1.0f + z);
                
                PushVertex( 1.0f + x, 1.0f + y, 1.0f + z);
                PushVertex( 1.0f + x, 0.0f + y, 0.0f + z);
                PushVertex( 1.0f + x, 1.0f + y, 0.0f + z);
                
                PushVertex( 1.0f + x, 0.0f + y, 0.0f + z);
                PushVertex( 1.0f + x, 1.0f + y, 1.0f + z);
                PushVertex( 1.0f + x, 0.0f + y, 1.0f + z);
                
                PushVertex( 1.0f + x, 1.0f + y, 1.0f + z);
                PushVertex( 1.0f + x, 1.0f + y, 0.0f + z);
                PushVertex( 0.0f + x, 1.0f + y, 0.0f + z);
                
                PushVertex( 1.0f + x, 1.0f + y, 1.0f + z);
                PushVertex( 0.0f + x, 1.0f + y, 0.0f + z);
                PushVertex( 0.0f + x, 1.0f + y, 1.0f + z);
                
                PushVertex( 1.0f + x, 1.0f + y, 1.0f + z);
                PushVertex( 0.0f + x, 1.0f + y, 1.0f + z);
                PushVertex( 1.0f + x, 0.0f + y, 1.0f + z);
			}
		}
	}

	GenerateVertexBuffer();
}

void Chunk::PushVertex(float x, float y, float z) 
{
    m_Vertices.push_back(x);
    m_Vertices.push_back(y);
    m_Vertices.push_back(z);
}

void Chunk::GenerateVertexBuffer()
{
	Renderer::DeleteBuffer(m_VertexBufferID);
	m_VertexBufferID = Renderer::GenerateBuffer(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data());
}

Voxel* Chunk::GetVoxel(int x, int y, int z) 
{
	return nullptr;
}