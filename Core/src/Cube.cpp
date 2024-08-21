#include "Cube.h"
#include "Renderer.h"

Cube::Cube()
{
	m_Vertices.reserve(8 * 3);
	m_Vertices = {
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

	GenerateVertexBuffer();
}

Cube::~Cube() {}