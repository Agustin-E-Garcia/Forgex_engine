#pragma once
#include "Exports.h"

class ENGINE_API Renderer
{
public:
	Renderer();
	~Renderer();

	void Draw();

private:
	unsigned int vertexArrayID;
	unsigned int vertexBuffer;
	unsigned int shaderID;
	unsigned int textureID;
	unsigned int uvBuffer;
};