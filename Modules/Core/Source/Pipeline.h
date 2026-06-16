#pragma once
#include "CoreExports.h"
#include "Interfaces/IPipelineStep.h"
#include <vector>

namespace Forgex::Core
{
    template<typename... Components>
    class CORE_API Pipeline
    {
    public:
        template<typename T, typename... Args>
        void RegisterStep(Args&&... args)
        {
            static_assert(std::is_base_of<Interfaces::IPipelineStep<Components...>, T>::value, "T must inherit from IPipelineStep");
            m_PipelineSteps.push_back(new T(std::forward<Args>(args)...));
        }

        virtual void Execute(Components&... components) const
        {
            for(Interfaces::IPipelineStep<Components...>* step : m_PipelineSteps)
            {
                step->Execute(components...);
            }
        }

    private:
        std::vector<Interfaces::IPipelineStep<Components...>*> m_PipelineSteps;
    };
}
