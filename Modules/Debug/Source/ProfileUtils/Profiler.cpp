#include "Profiler.h"
#include <algorithm>

namespace Forgex::Debug
{
    Profiler::Profiler() {}
    Profiler::~Profiler() {}

    void Profiler::AddResult(const long long duration)
    {
        auto it = m_Results.find(m_ActivePath);
        if(it != m_Results.end())
        {
            it->second.m_Buffer.Push(duration);
        }
        else
        {
            ProfileResult result;
            result.m_Buffer.Push(duration);
            result.m_Path = m_ActivePath;
            result.m_Depth = m_Depth;

            m_Results[m_ActivePath] = result;
        }
    }

    void Profiler::Clear()
    {
        m_Results.clear();
    }

    ProfileGatherer::ProfileGatherer(Profiler* profiler, const std::string& name)
        : m_Name(name), m_Profiler(profiler), m_StartTime(std::chrono::high_resolution_clock::now())
    {
        m_Profiler->PushScope(name);
    }

    ProfileGatherer::~ProfileGatherer()
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_StartTime).count();
        m_Profiler->AddResult(duration / 1000);
        m_Profiler->PopScope();
    }
}
