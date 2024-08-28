#include "Renderer.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Log.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"
#include "Camera.h"

Renderer::Renderer() 
{ 
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	LOG_CORE_INFO("Renderer initialized successfully");

	colorShaderID = ShaderLoader::LoadShader("Resources/Shaders/VoxelVertexShader.vertexshader", "Resources/Shaders/VoxelFragmentShader.fragmentshader");
	textureShaderID = ShaderLoader::LoadShader("Resources/Shaders/TextureVertexShader.vertexshader", "Resources/Shaders/TextureFragmentShader.fragmentshader");
	textureID = TextureLoader::LoadTexture("Resources/Textures/0.png");
}

Renderer::~Renderer() 
{
	glDeleteTextures(1, &textureID);
	glDeleteProgram(textureShaderID);
	glDeleteProgram(colorShaderID);
	glDeleteVertexArrays(1, &vertexArrayID);
}

void Renderer::ClearScreen() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(DrawInfo info)
{
	glm::mat4 Projection = m_ActiveCamera->GetProjectionMatrix();
	glm::mat4 View = m_ActiveCamera->GetViewMatrix();
	glm::mat4 Model = info.modelMatrix;

	glm::mat4 mvp = Projection * View * Model;

	glUseProgram(textureShaderID);

	unsigned int MatrixID = glGetUniformLocation(textureShaderID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	
	unsigned int TexID = glGetUniformLocation(textureShaderID, "myTextureSampler");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(TexID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, info.vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.indexBufferID);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, info.uvBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawElements(GL_TRIANGLES, info.indexCount, GL_UNSIGNED_INT, (void*)0);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Renderer::DrawVoxel(DrawInfo info)
{
	glm::mat4 Projection = m_ActiveCamera->GetProjectionMatrix();
	glm::mat4 View = m_ActiveCamera->GetViewMatrix();
	glm::mat4 Model = info.modelMatrix;

	glm::mat4 mvp = Projection * View * Model;

	glUseProgram(colorShaderID);

	unsigned int MatrixID = glGetUniformLocation(colorShaderID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	unsigned int TexID = glGetUniformLocation(colorShaderID, "textureSampler");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(TexID, 0);

	glm::uvec2 atlasSize = glm::uvec2(16, 16);
	unsigned int atlasID = glGetUniformLocation(colorShaderID, "AtlasSize");
	glUniform2uiv(atlasID, 1, &atlasSize[0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, info.vertexBufferID);
	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, info.indexCount);
	glDisableVertexAttribArray(0);
}

void Renderer::SetActiveCamera(Camera* activeCamera)
{
	m_ActiveCamera = activeCamera;
}

unsigned int Renderer::GenerateBuffer(unsigned int target, int size, const void* data)
{
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, size, data, GL_STATIC_DRAW);
	return buffer;
}

void Renderer::DeleteBuffer(unsigned int bufferID)
{
	glDeleteBuffers(1, &bufferID);
}