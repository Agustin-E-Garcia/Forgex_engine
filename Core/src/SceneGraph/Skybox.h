#pragma once
#include "Exports.h"
#include <vector>

struct DrawInfo;

class ENGINE_API Skybox
{
public:
	Skybox(std::vector<const char*> skyboxTextures);
	~Skybox() {}

	DrawInfo GetDrawInfo();

private:
	std::vector<float> m_Vertices;

	unsigned int m_VertexBufferID;
	unsigned int m_ShaderID;
	unsigned int m_TextureID;
};