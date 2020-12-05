#include <iostream>
#include <thread>
#include "ItemThreadPool.h"


ItemThreadPool::ItemThreadPool()
{
    m_pool = CreateThreadpool(nullptr);
    if (m_pool == nullptr)
    {
        return;
        // throw std::exception("Could not create a thread pool!");
    }

    InitializeThreadpoolEnvironment(&m_environment);
    SetThreadpoolCallbackPool(&m_environment, m_pool);

    m_cleanupGroup = CreateThreadpoolCleanupGroup();
    if (m_cleanupGroup == nullptr)
    {
        DestroyThreadpoolEnvironment(&m_environment);
        CloseThreadpool(m_pool);
        return;
        //  throw std::exception("Could not create a thread pool clean-up group!");
    }
    SetThreadpoolCallbackCleanupGroup(&m_environment, m_cleanupGroup, nullptr);
    m_work = CreateThreadpoolWork(SortStringParts, &m_taskQueue, &m_environment);
}

ItemThreadPool::ItemThreadPool(int minThreads, int maxThreads) : ItemThreadPool()
{
    SetThreadpoolThreadMaximum(m_pool, maxThreads);
    SetThreadpoolThreadMinimum(m_pool, minThreads);
}


void ItemThreadPool::SubmitCallbackTask(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end)
{
    m_taskQueue.push({ begin, end });
    SubmitThreadpoolWork(m_work);
}

void ItemThreadPool::WaitAndClose()
{
    CloseThreadpoolCleanupGroupMembers(m_cleanupGroup, false, nullptr);
    CloseThreadpoolCleanupGroup(m_cleanupGroup);
    CloseThreadpool(m_pool);
}

ItemThreadPool::~ItemThreadPool()
{

}

void ItemThreadPool::SortStringParts(PTP_CALLBACK_INSTANCE, void* context, PTP_WORK)
{
    auto taskQueue = static_cast<SynchronizedQueue<Task>*>(context);
    Task sortTask = taskQueue->pop();

    std::sort(sortTask.begin, sortTask.end);
}
