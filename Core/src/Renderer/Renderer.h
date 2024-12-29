#pragma once
#include "Exports.h"
#include <optional>
#include <glm/glm.hpp>

class Camera;
class Framebuffer;

struct DrawInfo
{
	unsigned int vertexBufferID;
	unsigned int indexBufferID;
	unsigned int uvBufferID;
	unsigned int shaderID;
	unsigned int textureID;

	glm::mat4 modelMatrix;
	unsigned int indexCount;
};

struct ENGINE_API RenderTarget
{
	unsigned int m_RenderTextureID;

	int m_TargetWidth;
	int m_TargetHeight;
};

class ENGINE_API Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void Draw(DrawInfo info) const;
	void DrawVoxel(DrawInfo info) const;
	void SetActiveCamera(Camera* activeCamera);
	void SetRenderTarget(RenderTarget& renderTarget) const;

	void PreSceneRender() const;
	void PostSceneRender() const;
	void DrawSkybox(DrawInfo info) const;

	static unsigned int GenerateBuffer(unsigned int target, int size, const void* data);
	static unsigned int GenerateVertexBuffer(int size, const void* data);
	static void DeleteBuffer(unsigned int bufferID);
	static void ToggleWireframe(bool wireframe);
	static void ToggleFaceCulling(bool faceCulling);

private:
	Framebuffer* m_SceneFramebuffer;

	unsigned int vertexArrayID;

	unsigned int colorShaderID;
	unsigned int textureShaderID;

	unsigned int textureID;

	Camera* m_ActiveCamera;
};