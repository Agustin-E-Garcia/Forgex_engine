#include "ServiceLocator.h"
#include "EngineCore.h"

namespace Forgex::Core
{
    ServiceLocator& ServiceLocator::Get()
    {
        static ServiceLocator instance;
        return instance;
    }
}
