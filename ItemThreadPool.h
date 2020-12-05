#pragma once
#pragma once
#include <Windows.h>
#include <string>
#include "SynchronizedQueue.h"

using Task = struct
{
    std::vector<std::string>::iterator begin;
    std::vector<std::string>::iterator end;
};

class ItemThreadPool
{

public:
    ItemThreadPool();
    ItemThreadPool(int minThreads, int maxThreads);

    void SubmitCallbackTask(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);

    void WaitAndClose();

    ~ItemThreadPool();
private:
    static void CALLBACK SortStringParts(PTP_CALLBACK_INSTANCE, void* context, PTP_WORK);

    PTP_POOL m_pool;
    TP_CALLBACK_ENVIRON m_environment;
    PTP_CLEANUP_GROUP m_cleanupGroup;
    PTP_WORK m_work;

    SynchronizedQueue<Task> m_taskQueue;
};



