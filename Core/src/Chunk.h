#pragma once
#include "Voxel.h"
#include "vector"

struct DrawInfo;

class ENGINE_API Chunk
{
public:
	Chunk();
	~Chunk();

	DrawInfo GetDrawInfo();
	Voxel* GetVoxel(int x, int y, int z);
private:
	static const int s_ChunkSize;

	std::vector<Voxel*> m_Voxels;

	std::vector<uint32_t> m_Vertices;
	unsigned int m_VertexBufferID;

	int FlattenIndex(int x, int y, int z);
	void GenerateVertices();
	void PushVertexData(uint8_t x, uint8_t y, uint8_t z, uint8_t blockType);
	void GenerateBuffers();
};