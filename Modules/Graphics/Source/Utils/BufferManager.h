#pragma once

namespace Forgex::Graphics::Utils
{
    enum BufferType
    {
        VertexBuffer = 0x8892,
        IndexBuffer = 0x8893,
        UVBuffer = 0x8892,
    };

    class BufferManager
    {
    public:
        static int GenerateBuffer(BufferType type, int size, const void* data);
        static void DeleteBuffer(unsigned int bufferID);
        static int GenerateVAO();
    };
}
