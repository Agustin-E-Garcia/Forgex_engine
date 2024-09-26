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
	void Draw(DrawInfo info) const;
	void DrawVoxel(DrawInfo info) const;
	void SetActiveCamera(Camera* activeCamera);

	static unsigned int GenerateBuffer(unsigned int target, int size, const void* data);
	static unsigned int GenerateVertexBuffer(int size, const void* data);
	static void DeleteBuffer(unsigned int bufferID);
	static void ToggleWireframe(bool wireframe);

private:
	unsigned int vertexArrayID;
	unsigned int colorShaderID;
	unsigned int textureShaderID;
	unsigned int textureID;

	Camera* m_ActiveCamera;
};