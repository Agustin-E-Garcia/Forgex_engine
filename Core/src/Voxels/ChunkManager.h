#pragma once
#include "../Exports.h"
#include "Chunk.h"

class DrawInfo;

class ENGINE_API ChunkManager 
{
public:
	ChunkManager();
	~ChunkManager();

	void Update();
	Chunk* GetChunkAtPosition(glm::vec3 position);
	Chunk* GetChunkAtWorldPosition(glm::vec3 worldPosition);
	std::vector<DrawInfo> GetDrawInfo();

private:
	unsigned int m_VertexKey;
	unsigned int m_FacesKey;

	unsigned int m_ChunkKeyX;
	unsigned int m_ChunkKeyZ;

	unsigned int m_LoadDistance = 10;
	unsigned int m_ChunkSize = 32;
	std::vector<Chunk*> m_ChunkCollection;

	int FlattenIndex(float x, float y, float z);
};