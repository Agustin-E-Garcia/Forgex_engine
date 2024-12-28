#include "pch.h"
#include "ChunkManager.h"
#include "SceneGraph/Object.h"
#include "SceneGraph/Scene.h"
#include "SceneGraph/Transform.h"
#include "Renderer/Renderer.h"
#include "Log.h"

ChunkManager::ChunkManager() : Component("Chunk Manager"), m_LastPlayerChunkPosition(glm::vec3(0)), m_PlayerObject(nullptr)
{
	glm::vec3 smallesPos = m_LastPlayerChunkPosition - glm::vec3(m_LoadDistance);
	glm::vec3 biggestPos = m_LastPlayerChunkPosition + glm::vec3(m_LoadDistance);

	for (int z = smallesPos.z; z <= biggestPos.z; z++)
	{
		for (int x = smallesPos.x; x <= biggestPos.x; x++)
		{
			glm::vec3 position = glm::vec3(x, 0, z);
			Chunk* newChunk = new Chunk(position);

			m_ChunkGrid.emplace(position, newChunk);
			m_ChunkLoadQueue.push(position);
		}
	}
}

ChunkManager::ChunkManager(const Object* player) : Component("Chunk Manager"), m_PlayerObject(player), m_LastPlayerChunkPosition(glm::vec3(0))
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
			m_ChunkMeshQueue.push(position);
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

void ChunkManager::OnUpdate(float deltaTime) 
{
	// Check if the player has moved to another chunk, if true we need to check which chunks to unload, and where to reuse them
	if (m_PlayerObject) 
	{
		glm::vec3 newPlayerChunkPos = GetChunkPositionFromWorld(m_PlayerObject->GetTransform()->GetPosition());

		if (newPlayerChunkPos != m_LastPlayerChunkPosition)
		{
			UnloadChunks(newPlayerChunkPos); // We check and unload the chunks that are farther than the draw distance to the player
			CheckChunksToLoad(newPlayerChunkPos); // We populate the updatequeue with the unloaded chunks giving them the new positions
		}

		m_LastPlayerChunkPosition = newPlayerChunkPos;
	}

	// We try to lower the impact of chunk loading/meshing by allowing only 10 chunks to be done per frame
	// This needs to be reworked into a multithreded system.
	// For now we can have the thread exist here, in the future we'll want a thread manager so we can deploy jobs to them with priorities
	//int chunksPerFrame = 10; 
	//while (!m_UpdateQueue.empty() && chunksPerFrame > 0)
	//{
	//	glm::vec3 position = m_UpdateQueue.front();
	//	Chunk* chunk = GetChunkAtPosition(position);
	//	m_UpdateQueue.pop();
	//
	//	if (!chunk) continue;
	//
	//	chunksPerFrame--;
	//
	//	std::vector<const Chunk*> adjacents;
	//	adjacents.emplace_back(GetChunkAtPosition(position + glm::vec3(-1, 0,  0)));
	//	adjacents.emplace_back(GetChunkAtPosition(position + glm::vec3( 1, 0,  0)));
	//	adjacents.emplace_back(GetChunkAtPosition(position + glm::vec3( 0, 0,  1)));
	//	adjacents.emplace_back(GetChunkAtPosition(position + glm::vec3( 0, 0, -1)));
	//
	//	if (!chunk->IsLoaded())
	//	{
	//		chunk->LoadChunk();
	//
	//		for (int i = 0; i < adjacents.size(); i++)
	//		{
	//			if (!adjacents[i]) continue;
	//			m_UpdateQueue.push(adjacents.at(i)->GetPosition());
	//		}
	//	}
	//
	//	if (!chunk->TryMeshChunk(adjacents, true)) m_UpdateQueue.push(position);
	//}

	// Trying new aproach where we'll be making two passes through all the chunks:
	// 1st Pass -> We load the subchunks and do face-culling locally in the chunk generating all the binary masks
	// 2nd Pass -> We request from neighbor chunks the required masks and do boundary checks for face-culling
	{
		int chunksPerFrame = 10;
		while (!m_ChunkLoadQueue.empty() && chunksPerFrame > 0)
		{
			glm::vec3 position = m_ChunkLoadQueue.front();
			Chunk* chunk = GetChunkAtPosition(position);
			m_ChunkLoadQueue.pop();
			
			if (!chunk) continue;

			chunk->LoadChunk();
			m_ChunkMeshQueue.push(position);

			chunksPerFrame--;
		}

		while (!m_ChunkMeshQueue.empty() && chunksPerFrame > 0)
		{
			glm::vec3 position = m_ChunkMeshQueue.front();
			Chunk* chunk = GetChunkAtPosition(position);

			if (chunk) 
			{
				std::vector<const Chunk*> adjacents;
				adjacents.emplace_back(GetChunkAtPosition(position + glm::vec3(-1, 0, 0)));
				adjacents.emplace_back(GetChunkAtPosition(position + glm::vec3(1, 0, 0)));
				adjacents.emplace_back(GetChunkAtPosition(position + glm::vec3(0, 0, 1)));
				adjacents.emplace_back(GetChunkAtPosition(position + glm::vec3(0, 0, -1)));

				if (!chunk->TryMeshChunk(adjacents, true)) break;
			}

			m_ChunkMeshQueue.pop();
			chunksPerFrame--;
		}
	}
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
			m_UnloadedChunks.emplace_back(chunk);
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

			m_ChunkLoadQueue.push(position);
			//m_ChunkMeshQueue.push(position);
			//m_ChunkMeshQueue.push(position + glm::vec3(-1, 0,  0));
			//m_ChunkMeshQueue.push(position + glm::vec3( 1, 0,  0));
			//m_ChunkMeshQueue.push(position + glm::vec3( 0, 0,  1));
			//m_ChunkMeshQueue.push(position + glm::vec3( 0, 0, -1));

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

void ChunkManager::DrawCustomEditor()
{
	ImGui::Text("Chunk size: %u", m_ChunkSize);
	ImGui::Text("Chunk draw distance: %u", m_LoadDistance);
	ImGui::Text("Chunk grid size: %u", m_ChunkGrid.size());
	ImGui::Text("Chunks queued to load: %u", m_ChunkMeshQueue.size());
	ImGui::Separator();
	
	bool exists = m_PlayerObject != nullptr;
	ImGui::Button(exists ? m_PlayerObject->GetName().c_str() : "Empty");
	if (ImGui::BeginDragDropTarget()) 
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_OBJECT")) 
		{
			IM_ASSERT(payload->DataSize == sizeof(uint32_t));
			m_PlayerObject = GetOwner()->GetScene()->FindObjectByID(*(uint32_t*)payload->Data);
		}
	}
	if (exists) 
	{
		ImGui::SameLine();
		if (ImGui::Button("Clear")) m_PlayerObject = nullptr;
	}
	ImGui::SameLine();
	ImGui::Text("Player Object");

	ImGui::InputFloat3("player chunk position", &m_LastPlayerChunkPosition.x);
}
