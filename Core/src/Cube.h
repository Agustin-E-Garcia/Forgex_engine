#pragma once
#include "Object.h"
#include <vector>

struct DrawInfo;

class ENGINE_API Cube : public Object
{
public:
	Cube();
	~Cube();

	DrawInfo GetDrawInfo();

private:
	std::vector<float> m_Vertices;
	std::vector<float> m_UVs;
	std::vector<unsigned int> m_Indices;

	unsigned int m_VertexBufferID = 0;
	unsigned int m_IndexBufferID = 0;
	unsigned int m_UVBufferID = 0;

	void GenerateBuffers();
};