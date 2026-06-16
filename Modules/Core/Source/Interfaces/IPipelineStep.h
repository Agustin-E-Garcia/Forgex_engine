#pragma once
#include "../CoreExports.h"

namespace Forgex::Core::Interfaces
{
    template<typename... Components>
    class CORE_API IPipelineStep
    {
    public:
        virtual void Execute(Components&... components) = 0;
    };
}
