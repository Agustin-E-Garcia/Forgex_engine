#include "Cube.h"
#include "Renderer.h"
#include "GL/glew.h"

Cube::Cube()
{
	m_Vertices.reserve(8 * 3);
	m_Vertices = 
	{
		// Front
		-1.0f, -1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		// Back
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
	};

	m_Indices.reserve(36);
	m_Indices =
	{
		// Front
		0, 1, 2,
		0, 2, 3,
		// Back
		4, 5, 6,
		4, 6, 7,
		// Right
		1, 5, 6,
		1, 6, 2,
		// Left
		0, 4, 7,
		0, 7, 3,
		// Upper
		3, 2, 6,
		3, 6, 7,
		// Bottom
		0, 1, 5,
		0, 5, 4
	};

	m_UVs.reserve(35);
	m_UVs =
	{
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		0.335973f, 1.0f - 0.335903f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
	};

	GenerateBuffers();
}

Cube::~Cube() {}

DrawInfo Cube::GetDrawInfo()
{
	DrawInfo info{};
	info.vertexBufferID = m_VertexBufferID;
	info.indexBufferID = m_IndexBufferID;
	info.uvBufferID = m_UVBufferID;
	// shader
	// texture
	info.modelMatrix = GetModelMatrix();
	info.indexCount = m_Indices.size();

	return info;
}

void Cube::GenerateBuffers()
{
	m_VertexBufferID = Renderer::GenerateBuffer(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data());
	m_IndexBufferID = Renderer::GenerateBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data());
	m_UVBufferID = Renderer::GenerateBuffer(GL_ARRAY_BUFFER, m_UVs.size() * sizeof(float), m_UVs.data());
}