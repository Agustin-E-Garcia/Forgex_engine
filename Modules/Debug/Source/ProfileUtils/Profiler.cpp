#include "Profiler.h"

namespace Forgex::Debug
{
    Profiler::Profiler() {}
    Profiler::~Profiler() {}

    void Profiler::AddResult(const std::string name, const long long duration)
    {
        m_Results[name].m_Duration += duration;
        m_Results[name].m_Samples += 1;
    }

    void Profiler::Clear()
    {
        m_Results.clear();
    }

    ProfileGatherer::ProfileGatherer(Profiler* profiler, const std::string& name)
        : m_Name(name), m_Profiler(profiler), m_StartTime(std::chrono::high_resolution_clock::now())
    {
    }

    ProfileGatherer::~ProfileGatherer()
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_StartTime).count();
        m_Profiler->AddResult(m_Name, duration / 1000);
    }
}
