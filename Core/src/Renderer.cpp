#include "Renderer.h"
#include <GL/glew.h>
#include "Log.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

static const float g_vertex_buffer_data[] = 
{
   -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   -0.5f,  0.5f, 0.0f,
   0.5f, 0.5f, 0.0f
};

static const float g_uv_buffer_data[] =
{
   0.0f, 0.0f,
   1.0f, 0.0f,
   0.0f, 1.0f,
   1.0f, 1.0f
};

Renderer::Renderer() 
{ 
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	LOG_CORE_INFO("Renderer initialized successfully");

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	shaderID = ShaderLoader::LoadShader("Resources/Shaders/SimpleVertexShader.vertexshader", "Resources/Shaders/SimpleFragmentShader.fragmentshader");
	textureID = TextureLoader::LoadTexture("Resources/Textures/uvtemplate.bmp");

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}

Renderer::~Renderer() 
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteProgram(shaderID);
}

void Renderer::Draw()
{
	LOG_CORE_TRACE("Renderer::Draw");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	unsigned int texID = glGetUniformLocation(shaderID, "myTextureSampler");
	glUniform1i(texID, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer
	(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer
	(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}