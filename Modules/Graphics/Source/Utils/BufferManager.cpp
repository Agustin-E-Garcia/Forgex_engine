#include "BufferManager.h"
#include <gl/glew.h>

namespace Forgex::Graphics::Utils
{
    int BufferManager::GenerateBuffer(BufferType type, int size, const void* data)
    {
        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(type, buffer);
        glBufferData(type, size, data, GL_STATIC_DRAW);
        return buffer;
    }

    void BufferManager::DeleteBuffer(unsigned bufferID)
    {
        glDeleteBuffers(1, &bufferID);
    }

    int BufferManager::GenerateVBO()
    {
        unsigned int VBO;
        glGenVertexArrays(1, &VBO);
        glBindVertexArray(VBO);
        return VBO;
    }
}
