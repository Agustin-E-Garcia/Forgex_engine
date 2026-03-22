#pragma once
#include "ServiceLocator.h"
#include <ForgexDebug.h>

namespace Forgex::Core
{
    // Logs
    #define LOG_CORE(...)      Forgex::Core::ServiceLocator::Get().Fetch<Debug::DebugManager>()->GetLogManager()->CoreLog(__VA_ARGS__)
    #define LOG_CLIENT(...)    Forgex::Core::ServiceLocator::Get().Fetch<Debug::DebugManager>()->GetLogManager()->ClientLog(__VA_ARGS__)

    // Commands
    #define REGISTER_COMMAND(...) Forgex::Core::ServiceLocator::Get().Fetch<Debug::DebugManager>()->GetCommandHandler()->Register(__VA_ARGS__)

    // Profiler
    #define PROFILE_FUNCTION(x) Debug::ProfileGatherer profiler = Debug::ProfileGatherer(Forgex::Core::ServiceLocator::Get().Fetch<Debug::DebugManager>()->GetProfiler(), x)
}
