#pragma once
#include <GL/glew.h>

namespace Forgex::Graphics::Utils::Buffers
{
    int GenerateBuffer(GLuint type, int size, const void* data);
    void DeleteBuffer(unsigned int bufferID);
    int GenerateVAO();
    int GenerateUBO(int size);
}
