#pragma once
#include "ProfileUtils/Profiler.h"
#include "CommandUtils/CommandHandler.h"
#include "LogUtils/Log.h"

namespace Forgex::Debug
{
    class DebugManager
    {
    public:
        DebugManager() {}
        ~DebugManager() {}

        Profiler* GetProfiler() { return &m_Profiler; }
        CommandHandler* GetCommandHandler() { return &m_CommandHandler; }
        LogManager* GetLogManager() { return &m_LogManager; }

    private:
        Profiler m_Profiler;
        CommandHandler m_CommandHandler;
        LogManager m_LogManager;
    };
}