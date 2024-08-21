#pragma once
#include "Exports.h"
#include <optional>
#include <glm/glm.hpp>

struct DrawInfo
{
	unsigned int vertexBufferID;
	unsigned int uvBufferID;
	unsigned int shaderID;
	std::optional<unsigned int> textureID;

	glm::mat4 modelMatrix;
};

class ENGINE_API Renderer
{
public:
	Renderer();
	~Renderer();

	void Draw();

	static unsigned int GenerateBuffer(size_t size, const float* data);

private:
	unsigned int vertexArrayID;
	unsigned int vertexBuffer;
	unsigned int shaderID;
	unsigned int textureID;
	unsigned int uvBuffer;
};