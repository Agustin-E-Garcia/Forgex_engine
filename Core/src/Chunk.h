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

	std::vector<float> m_Vertices;
	unsigned int m_VertexBufferID;

	void GenerateVertices();
	void PushVertex(float x, float y, float z);
	void GenerateVertexBuffer();
};