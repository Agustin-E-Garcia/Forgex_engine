#pragma once
#include "GraphicsExports.h"
#include <ForgexCore.h>

namespace Forgex::Graphics
{
    class GRAPHICS_API GraphicsModule : public Core::Interfaces::IModule
    {
    public:
        void Init(Core::EngineCore& core) override;
        void Shutdown() override;

        const char* GetName() const override { return "Graphics_Module"; }

    private:
        int m_VertexBufferObjectID;
        int m_UniformBufferObjectID;
    };
}
