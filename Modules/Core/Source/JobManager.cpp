#include "JobManager.h"

namespace Forgex::Core
{
    JobManager::JobManager(int threadCount)
    {
        for(int i = 0; i < threadCount; i++)
            m_Threads.emplace_back(&JobManager::WorkerLoop, this);
    }

    JobManager::~JobManager() 
    {
        {
            std::lock_guard lock(m_QueueMutex);
            m_Stop = true;
        }
        m_Condition.notify_all();
        for (std::thread& thread : m_Threads)
            thread.join();
    }

    void JobManager::WorkerLoop()
    {
        while(true)
        {
            std::function<void()> job;
            {
                std::unique_lock lock(m_QueueMutex);
                m_Condition.wait(lock, [this] { return m_Stop || !m_JobQueue.empty(); });

                if(m_Stop && m_JobQueue.empty()) return;

                job = std::move(m_JobQueue.front());
                m_JobQueue.pop();
            }
            job();
        }
    }
}
