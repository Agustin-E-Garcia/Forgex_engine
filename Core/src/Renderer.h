#pragma once
#include "Exports.h"
#include <optional>
#include <glm/glm.hpp>

class Camera;

struct DrawInfo
{
	unsigned int vertexBufferID;
	unsigned int indexBufferID;
	unsigned int uvBufferID;
	unsigned int shaderID;
	std::optional<unsigned int> textureID;

	glm::mat4 modelMatrix;
	unsigned int indexCount;
};

class ENGINE_API Renderer
{
public:
	Renderer();
	~Renderer();

	void ClearScreen();
	void Draw(DrawInfo info);
	void SetActiveCamera(Camera* activeCamera);

	static unsigned int GenerateBuffer(unsigned int target, int size, const void* data);

private:
	unsigned int vertexArrayID;
	unsigned int shaderID;
	unsigned int textureID;

	Camera* m_ActiveCamera;
};