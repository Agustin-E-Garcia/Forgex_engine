#pragma once
#include "../DebugExports.h"
#include <ForgexDataStructures.h>
#include <chrono>
#include <string>
#include <unordered_map>

namespace Forgex::Debug
{
    struct ProfileResult
    {
        std::string m_Path;
        int m_Depth;

        DataStructures::RingBuffer<long long> m_Buffer;
    };

    class DEBUG_API Profiler
    {
    public:
        Profiler();
        ~Profiler();

        void AddResult(const long long duration);
        void Clear();
        const std::unordered_map<std::string, ProfileResult>& GetResults() const { return m_Results; }

        void PushScope(std::string scopeName)
        {
            m_ActivePath += "/" + scopeName;
            m_Depth++;
        }

        void PopScope()
        {
            const size_t lastSlash = m_ActivePath.find_last_of('/');
            if (lastSlash != std::string::npos)
            {
                m_ActivePath.erase(lastSlash);
                m_Depth--;
            }
        }

    private:
        std::string m_ActivePath;
        int m_Depth = 0;

        std::unordered_map<std::string, ProfileResult> m_Results;
    };

    class DEBUG_API ProfileGatherer
    {
    public:
        ProfileGatherer(Profiler* profiler, const std::string& name);
        ~ProfileGatherer();

    private:
        std::string m_Name;
        Profiler* m_Profiler;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    };
}
