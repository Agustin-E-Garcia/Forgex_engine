#include "BufferManager.h"

namespace Forgex::Graphics::Utils::Buffers
{
    int GenerateBuffer(GLuint type, int size, const void* data)
    {
        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(type, buffer);
        glBufferData(type, size, data, GL_STATIC_DRAW);
        return buffer;
    }

    void DeleteBuffer(unsigned bufferID)
    {
        glDeleteBuffers(1, &bufferID);
    }

    int GenerateVAO()
    {
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        return VAO;
    }

    int GenerateUBO(int size)
    {
        unsigned int UBO;
        glGenBuffers(1, &UBO);
        glBindBuffer(GL_UNIFORM_BUFFER, UBO);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);

        return UBO;
    }
}
