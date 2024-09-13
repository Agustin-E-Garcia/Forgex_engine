#pragma once
#include "Voxel.h"
#include "../Renderer.h"
#include <vector>
#include <glm/glm.hpp>

#include <future>

struct DrawInfo;
class ChunkManager;

class ENGINE_API Subchunk
{
	friend class Chunk;
public:
	Subchunk();
	~Subchunk();

private:
	std::vector<Voxel> m_Voxels;
	std::vector<uint32_t> m_Vertices;
	std::vector<uint32_t> m_BinaryMap;

	bool m_UptoDate;

	int FlattenIndex(int x, int y, int z);
	int FlattenIndex(int x, int z);
	uint32_t GetBinaryMap(int x, int z);

	void BinaryMeshing(int subChunkIndex, std::vector<uint32_t> top, std::vector<uint32_t> bottom, std::vector<uint32_t> right, std::vector<uint32_t> left, std::vector<uint32_t> front, std::vector<uint32_t> back);
	void PushVertexData(uint8_t x, uint8_t y, uint8_t z, uint8_t blockType);
	void CopyVertices(std::vector<uint32_t>* vertices);
};

class ENGINE_API Chunk
{
public:
	Chunk(glm::vec3 chunkPosition);
	~Chunk();

	void Update(std::vector<Chunk*> adjacentChunks);
	void BuildMesh(std::vector<Chunk*> adjacentChunks);
	void LoadChunk(glm::vec3 newPosition);

	inline const Subchunk* GetSubchunk(int index) { return index >= 0 && index < m_SubChunks.size() ? &m_SubChunks[index] : nullptr; }
	inline glm::vec3 GetPosition() { return m_ChunkPosition; }
	inline DrawInfo GetDrawInfo() { return m_DrawInfo; }
	inline bool NeedsUpdate() { return !m_UpToDate; }

private:
	glm::vec3 m_ChunkPosition;

	std::vector<Subchunk> m_SubChunks;

	unsigned int m_VertexBufferID;
	DrawInfo m_DrawInfo;

	bool m_UpToDate;

	void GenerateBuffers();
	void UpdateDrawInfo();

	inline void SetPosition(glm::vec3 newPosition) { m_ChunkPosition = newPosition; }
};