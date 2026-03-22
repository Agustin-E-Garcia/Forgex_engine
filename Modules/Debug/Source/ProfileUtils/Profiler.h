#pragma once
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

    class Profiler
    {
    public:
        Profiler();
        ~Profiler();

        void AddResult(const std::string name, const long long duration);
        void Clear();
        const std::unordered_map<std::string, ProfileResult>& GetResults() const { return m_Results; }

    private:
        std::unordered_map<std::string, ProfileResult> m_Results;
    };

    class ProfileGatherer
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
