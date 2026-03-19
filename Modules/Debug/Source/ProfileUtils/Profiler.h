#pragma once
#include "../DebugExports.h"
#include <chrono>
#include <string>
#include <unordered_map>

namespace Forgex::Debug
{
    struct ProfileResult
    {
        float m_Duration = 0;
        int m_Samples = 0;
    };

    class DEBUG_API Profiler
    {
    public:
        static Profiler& Get();

        void AddResult(const std::string name, const long long duration);
        void Clear();
        const std::unordered_map<std::string, ProfileResult>& GetResults() const { return m_Results; }

    private:
        Profiler() = default;
        Profiler(const Profiler&) = delete;
        Profiler(Profiler&&) = delete;
        Profiler& operator=(const Profiler&) = delete;
        Profiler& operator=(Profiler&&) = delete;

        std::unordered_map<std::string, ProfileResult> m_Results;
    };

    class DEBUG_API ProfileGatherer
    {
    public:
        ProfileGatherer(const std::string& name);
        ~ProfileGatherer();

    private:
        std::string m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    };

#define PROFILE_FUNCTION(...) Debug::ProfileGatherer profiler = Debug::ProfileGatherer(__VA_ARGS__);
}
