#pragma once
#include "../Exports.h"
#include "Chunk.h"
#include <unordered_map>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

class DrawInfo;

class ENGINE_API ChunkManager 
{
public:
	ChunkManager(glm::vec3 playerPosition);
	~ChunkManager();

	void Update(glm::vec3 playerPosition);
	Chunk* GetChunkAtPosition(glm::vec3 position) const;
	glm::vec3 GetChunkPositionFromWorld(glm::vec3 worldPosition);
	std::vector<DrawInfo> GetDrawInfo();

private:
	unsigned int m_ChunkKeyX;
	unsigned int m_ChunkKeyZ;
	unsigned int m_ChunkCountKey;
	unsigned int m_VoxelCountKey;

	glm::vec3 m_LastPlayerChunkPosition;

	unsigned int m_LoadDistance = 16;
	unsigned int m_ChunkSize = 16;

	std::unordered_map<glm::vec3, Chunk*> m_ChunkGrid;

	std::vector<Chunk*> m_UnloadedChunks;
	std::vector<glm::vec3> m_ChunksToLoad;
	std::vector<Chunk*> m_LoadedChunks;

	void UnloadChunks(glm::vec3 direction);
	void CheckChunksToLoad(glm::vec3 playerPosition);
};