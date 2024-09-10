#pragma once
#include "Voxel.h"
#include "../Renderer.h"
#include <vector>
#include <glm/glm.hpp>

#include <future>

struct DrawInfo;
class ChunkManager;

class ENGINE_API Chunk
{
public:
	Chunk(glm::vec3 chunkPosition, int chunkSize);
	~Chunk();

	bool Update(ChunkManager& manager);
	void SetupChunk();
	void LoadChunk(glm::vec3 newPosition);

	bool TryGetVoxelAtPosition(float x, float y, float z, Voxel& voxel);
	bool IsVoxelActive(float x, float y, float z);

	inline glm::vec3 GetPosition() { return m_ChunkPosition; }
	inline DrawInfo GetDrawInfo() { return m_DrawInfo; }

private:
	int m_ChunkSize;
	const int m_ChunkSizeY = 255;
	glm::vec3 m_ChunkPosition;

	std::vector<Voxel> m_Voxels;
	std::vector<uint32_t> m_Vertices;
	unsigned int m_VertexBufferID;
	DrawInfo m_DrawInfo;

	bool m_UpToDate;

	int FlattenIndex(int x, int y, int z);
	void PushVertexData(uint8_t x, uint8_t y, uint8_t z, uint8_t blockType);
	
	void GenerateVertices(ChunkManager& manager);
	void GenerateBuffers();
	void UpdateDrawInfo();

	inline void SetPosition(glm::vec3 newPosition) { m_ChunkPosition = newPosition; }
};