#include "ChunkManager.h"
#include "../Renderer.h"
#include "../Profiler.h"
#include "../Log.h"

ChunkManager::ChunkManager(const Object* player) : Object("Chunk Manager"), m_PlayerObject(player), m_LastPlayerChunkPosition(glm::vec3(0))
{
	if (!m_PlayerObject) 
	{
		LOG_CORE_ERROR("ChunkManager::Player is nullptr");
		return;
	}

	m_LastPlayerChunkPosition = GetChunkPositionFromWorld(player->GetTransform()->GetPosition());
	glm::vec3 smallesPos = m_LastPlayerChunkPosition - glm::vec3(m_LoadDistance);
	glm::vec3 biggestPos = m_LastPlayerChunkPosition + glm::vec3(m_LoadDistance);

	for (int z = smallesPos.z; z <= biggestPos.z; z++)
	{
		for (int x = smallesPos.x; x <= biggestPos.x; x++)
		{
			glm::vec3 position = glm::vec3(x, 0, z);
			Chunk* newChunk = new Chunk(position);
			
			m_ChunkGrid.emplace(position, newChunk);
			m_UpdateQueue.push(position);
		}
	}
}

ChunkManager::~ChunkManager()
{
	for (auto it = m_ChunkGrid.begin(); it != m_ChunkGrid.end();) 
	{
		delete it->second;
		it = m_ChunkGrid.erase(it);
	}
}

void ChunkManager::Update(float deltaTime) 
{
	glm::vec3 newPlayerChunkPos = GetChunkPositionFromWorld(m_PlayerObject->GetTransform()->GetPosition());

	if (newPlayerChunkPos != m_LastPlayerChunkPosition)
	{
		UnloadChunks(newPlayerChunkPos);
		CheckChunksToLoad(newPlayerChunkPos);
	}

	int chunksPerFrame = 10;
	while (!m_UpdateQueue.empty() && chunksPerFrame > 0)
	{
		glm::vec3 position = m_UpdateQueue.front();
		Chunk* chunk = GetChunkAtPosition(position);
		m_UpdateQueue.pop();

		if (!chunk) continue;

		chunksPerFrame--;

		std::vector<const Chunk*> adjacents;
		adjacents.push_back(GetChunkAtPosition(position + glm::vec3(-1, 0, 0)));
		adjacents.push_back(GetChunkAtPosition(position + glm::vec3(1, 0, 0)));
		adjacents.push_back(GetChunkAtPosition(position + glm::vec3(0, 0, 1)));
		adjacents.push_back(GetChunkAtPosition(position + glm::vec3(0, 0, -1)));

		if (!chunk->IsLoaded())
		{
			chunk->LoadChunk();

			for (int i = 0; i < adjacents.size(); i++)
			{
				if (!adjacents[i]) continue;
				m_UpdateQueue.push(adjacents.at(i)->GetPosition());
			}
		}

		if (!chunk->TryMeshChunk(adjacents, true)) m_UpdateQueue.push(position);
	}

	m_LastPlayerChunkPosition = newPlayerChunkPos;
}

void ChunkManager::Render(const Renderer& renderer)
{
	for (auto it = m_ChunkGrid.begin(); it != m_ChunkGrid.end(); it++)
	{
		renderer.DrawVoxel(it->second->GetDrawInfo());
	}
}

void ChunkManager::UnloadChunks(glm::vec3 playerPosition)
{
	glm::vec3 direction = glm::normalize(playerPosition - m_LastPlayerChunkPosition);

	for (auto it = (--m_ChunkGrid.end());; --it)
	{
		glm::vec3 distanceVector = (playerPosition - it->first) * direction;
		int distance = abs(distanceVector.x) + abs(distanceVector.z);

		if (distance > m_LoadDistance)
		{
			Chunk* chunk = it->second;
			m_UnloadedChunks.push_back(chunk);
			it = m_ChunkGrid.erase(it);
		}

		if (it == m_ChunkGrid.begin()) break;
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

			chunk->ChangePosition(position);

			m_UpdateQueue.push(position);
			m_UpdateQueue.push(position + glm::vec3(-1, 0,  0));
			m_UpdateQueue.push(position + glm::vec3( 1, 0,  0));
			m_UpdateQueue.push(position + glm::vec3( 0, 0,  1));
			m_UpdateQueue.push(position + glm::vec3( 0, 0, -1));

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

	return glm::vec3(x, 0, z);
}