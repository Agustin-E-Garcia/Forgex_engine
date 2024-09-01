#include "ChunkManager.h"
#include "../Renderer.h"
#include "../Profiler.h"

ChunkManager::ChunkManager()
{
	m_ChunkCollection.reserve(std::pow(m_LoadDistance, 2));
	for (int z = 0; z < m_LoadDistance; z++)
	{
		for (int x = 0; x < m_LoadDistance; x++)
		{
			Chunk* newChunk = new Chunk(glm::vec3(x, 0, z), 32);
			newChunk->LoadChunk();

			m_ChunkCollection.push_back(newChunk);
		}
	}

	m_VertexKey = Profiler::AddProfile("Vertices", 0);
	m_FacesKey = Profiler::AddProfile("Faces", 0);
	m_ChunkKeyX = Profiler::AddProfile("Chunk X", 0);
	m_ChunkKeyZ = Profiler::AddProfile("Chunk Z", 0);
}

ChunkManager::~ChunkManager()
{
	for (int i = m_ChunkCollection.size() - 1; i >= 0; i--)
	{
		delete m_ChunkCollection[i];
	}
}

void ChunkManager::Update()
{
	for (int i = 0; i < m_ChunkCollection.size(); i++)
	{
		m_ChunkCollection[i]->Update(*this);
	}
}

Chunk* ChunkManager::GetChunkAtPosition(glm::vec3 position) 
{
	// For now we expect values to be in range, I will update this later when it's not 4:13am
	if (position.x < 0 || position.z < 0) return nullptr;
	if (position.x >= m_LoadDistance || position.z >= m_LoadDistance) return nullptr;

	int index = FlattenIndex(position.x, position.y, position.z);
	return index < m_ChunkCollection.size() ? m_ChunkCollection[index] : nullptr;
}

Chunk* ChunkManager::GetChunkAtWorldPosition(glm::vec3 worldPosition)
{
	int chunk_x = static_cast<int>(worldPosition.x) / 32;
	int chunk_z = static_cast<int>(worldPosition.z) / 32;

	Profiler::UpdateProfile(m_ChunkKeyX, chunk_x);
	Profiler::UpdateProfile(m_ChunkKeyZ, chunk_z);

	return nullptr;
}

std::vector<DrawInfo> ChunkManager::GetDrawInfo()
{
	std::vector<DrawInfo> drawInfoCollection;

	int vertices = 0;
	for (int i = 0; i < m_ChunkCollection.size(); i++)
	{
		DrawInfo info = m_ChunkCollection[i]->GetDrawInfo();
		drawInfoCollection.push_back(info);
		vertices += info.indexCount;
	}

	Profiler::UpdateProfile(m_VertexKey, vertices);
	Profiler::UpdateProfile(m_FacesKey, vertices / 6);

	return drawInfoCollection;
}

int ChunkManager::FlattenIndex(float x, float y, float z) 
{
	return (z * m_LoadDistance) + x;
}