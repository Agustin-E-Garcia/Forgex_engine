#include "Profiler.h"

namespace Forgex::Debug
{
    Profiler& Profiler::Get()
    {
        static Profiler instance;
        return instance;
    }

    void Profiler::AddResult(const std::string name, const long long duration)
    {
        m_Results[name].m_Duration += duration;
        m_Results[name].m_Samples += 1;
    }

    void Profiler::Clear()
    {
        m_Results.clear();
    }

    ProfileGatherer::ProfileGatherer(const std::string& name)
        : m_Name(name), m_StartTime(std::chrono::high_resolution_clock::now())
    {
    }

    ProfileGatherer::~ProfileGatherer()
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_StartTime).count();
        Profiler::Get().AddResult(m_Name, duration / 1000);
    }
}
