#pragma once
#include "Voxel.h"
#include <vector>
#include <glm/glm.hpp>

struct DrawInfo;
class ChunkManager;

class ENGINE_API Chunk
{
public:
	Chunk(glm::vec3 chunkPosition, int chunkSize);
	~Chunk();

	void Update(ChunkManager& manager);
	void LoadChunk();
	DrawInfo GetDrawInfo();

	Voxel* GetVoxelAtPosition(glm::vec3 position);
	bool IsVoxelActive(glm::vec3 position);
	glm::vec3 GetPosition() { return m_ChunkPosition; }

private:
	int m_ChunkSize;
	const int m_ChunkSizeY = 150;
	glm::vec3 m_ChunkPosition;

	std::vector<Voxel*> m_Voxels;
	std::vector<uint32_t> m_Vertices;
	unsigned int m_VertexBufferID;

	bool m_UpToDate;

	int FlattenIndex(int x, int y, int z);
	void GenerateVertices(ChunkManager& manager);
	void PushVertexData(uint8_t x, uint8_t y, uint8_t z, uint8_t blockType);
	void GenerateBuffers();
};