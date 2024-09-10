#include "ChunkManager.h"
#include "../Renderer.h"
#include "../Profiler.h"
#include "../Log.h"

ChunkManager::ChunkManager(glm::vec3 playerPosition)
{
	m_LastPlayerChunkPosition = GetChunkPositionFromWorld(playerPosition);
	glm::vec3 smallesPos = m_LastPlayerChunkPosition - glm::vec3(m_LoadDistance);
	glm::vec3 biggestPos = m_LastPlayerChunkPosition + glm::vec3(m_LoadDistance);

	for (int z = smallesPos.z; z <= biggestPos.z; z++)
	{
		for (int x = smallesPos.x; x <= biggestPos.x; x++)
		{
			glm::vec3 position = glm::vec3(x, 0, z);
			Chunk* newChunk = new Chunk(position, m_ChunkSize);
			
			m_ChunkGrid.emplace(position, newChunk);
		}
	}

	m_ChunkCountKey = Profiler::AddProfile("Chunks", 0);
	m_VoxelCountKey = Profiler::AddProfile("Voxels", 0);

	m_ChunkKeyX = Profiler::AddProfile("Chunk X", 0);
	m_ChunkKeyZ = Profiler::AddProfile("Chunk Z", 0);
}

ChunkManager::~ChunkManager()
{
	for (auto it = m_ChunkGrid.begin(); it != m_ChunkGrid.end();) 
	{
		delete it->second;
		it = m_ChunkGrid.erase(it);
	}
}

void ChunkManager::Update(glm::vec3 playerPosition)
{
	glm::vec3 newPlayerChunkPos = GetChunkPositionFromWorld(playerPosition);

	if (newPlayerChunkPos != m_LastPlayerChunkPosition)
	{
		UnloadChunks(newPlayerChunkPos);
		CheckChunksToLoad(newPlayerChunkPos);
	}

	for (auto it = m_ChunkGrid.begin(); it != m_ChunkGrid.end(); it++)
	{
		it->second->Update(*this);
	}

	m_LastPlayerChunkPosition = newPlayerChunkPos;
}

void ChunkManager::UnloadChunks(glm::vec3 playerPosition)
{
	glm::vec3 direction = glm::normalize(playerPosition - m_LastPlayerChunkPosition);

	for (auto it = (--m_ChunkGrid.end()); it != m_ChunkGrid.begin(); --it)
	{
		glm::vec3 distanceVector = (playerPosition - it->first) * direction;
		int distance = abs(distanceVector.x) + abs(distanceVector.z);

		if (distance > m_LoadDistance)
		{
			Chunk* chunk = it->second;
			m_UnloadedChunks.push_back(chunk);
			it = m_ChunkGrid.erase(it);
		}
	}
}

void ChunkManager::CheckChunksToLoad(glm::vec3 playerPosition)
{
	glm::vec3 smallesPos = m_LastPlayerChunkPosition - glm::vec3(m_LoadDistance);
	glm::vec3 biggestPos = m_LastPlayerChunkPosition + glm::vec3(m_LoadDistance);

	for (int z = smallesPos.z; z <= biggestPos.z; z++)
	{
		for (int x = smallesPos.x; x <= biggestPos.x; x++)
		{
			glm::vec3 position = glm::vec3(x, 0, z);
			bool exists = GetChunkAtPosition(position);
			if (exists) continue;

			if (m_UnloadedChunks.empty()) return;

			Chunk* chunk = m_UnloadedChunks.back();
			m_UnloadedChunks.pop_back();

			chunk->LoadChunk(position);

			m_ChunkGrid.emplace(position, chunk);
		}
	}
}

Chunk* ChunkManager::GetChunkAtPosition(glm::vec3 position) const
{	
	bool found = m_ChunkGrid.count(position);
	return found ? m_ChunkGrid.at(position) : nullptr;
}

glm::vec3 ChunkManager::GetChunkPositionFromWorld(glm::vec3 worldPosition)
{
	int x = worldPosition.x / m_ChunkSize;
	int z = worldPosition.z / m_ChunkSize;

	Profiler::UpdateProfile(m_ChunkKeyX, x);
	Profiler::UpdateProfile(m_ChunkKeyZ, z);

	return glm::vec3(x, 0, z);
}

std::vector<DrawInfo> ChunkManager::GetDrawInfo()
{
	std::vector<DrawInfo> drawInfoCollection;

	for (auto it = m_ChunkGrid.begin(); it != m_ChunkGrid.end(); it++)
	{
		DrawInfo info = it->second->GetDrawInfo();
		drawInfoCollection.push_back(info);
	}

	Profiler::UpdateProfile(m_ChunkCountKey, m_ChunkGrid.size());
	Profiler::UpdateProfile(m_VoxelCountKey, m_ChunkGrid.size() * (m_ChunkSize * 255 * m_ChunkSize));

	return drawInfoCollection;
}