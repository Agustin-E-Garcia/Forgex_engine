#pragma once
#include <future>
#include <memory>
#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <utility>

namespace Forgex::Core
{
    class JobManager
    {
    public:
        JobManager(int threadCount);
        ~JobManager();

        template <typename T>
        std::future<T> Enqueue(std::function<T()> job)
        {
            auto task = std::make_shared<std::packaged_task<T()>>(std::move(job));
            std::future<T> future = task->get_future();
            {
                std::lock_guard lock(m_QueueMutex);
                m_JobQueue.push([task]() { (*task)(); });
            }
            m_Condition.notify_one();
            return future;
        }

    private:
        void WorkerLoop();

        std::queue<std::function<void()>> m_JobQueue;
        std::vector<std::thread> m_Threads;
        std::mutex m_QueueMutex;
        std::condition_variable m_Condition;
        bool m_Stop = false;
    };
}
