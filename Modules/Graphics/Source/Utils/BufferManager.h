#pragma once

namespace Forgex::Graphics::Utils::Buffers
{
    int GenerateBuffer(unsigned int type, int size, const void* data);
    void DeleteBuffer(unsigned int bufferID);
    int GenerateVAO();
    int GenerateUBO(int size);
}
