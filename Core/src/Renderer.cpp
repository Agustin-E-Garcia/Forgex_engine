#include "Renderer.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Log.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

Renderer::Renderer() 
{ 
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	LOG_CORE_INFO("Renderer initialized successfully");

	shaderID = ShaderLoader::LoadShader("Resources/Shaders/SimpleVertexShader.vertexshader", "Resources/Shaders/SimpleFragmentShader.fragmentshader");
	textureID = TextureLoader::LoadTexture("Resources/Textures/uvtemplate.bmp");
}

Renderer::~Renderer() 
{
	glDeleteTextures(1, &textureID);
	glDeleteProgram(shaderID);
	glDeleteVertexArrays(1, &vertexArrayID);
}

void Renderer::ClearScreen() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(DrawInfo info)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(glm::vec3(4, 3, 3),glm::vec3(0, 0, 0),	glm::vec3(0, 1, 0));
	glm::mat4 Model = info.modelMatrix;

	glm::mat4 mvp = Projection * View * Model;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shaderID);

	unsigned int MatrixID = glGetUniformLocation(shaderID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	
	unsigned int TexID = glGetUniformLocation(shaderID, "myTextureSampler");
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

unsigned int Renderer::GenerateBuffer(unsigned int target, int size, const void* data)
{
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, size, data, GL_STATIC_DRAW);
	return buffer;
}