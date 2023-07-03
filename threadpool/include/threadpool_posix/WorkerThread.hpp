#pragma once
#include <signal.h>
#include <pthread.h>
#include <iostream>
#include <threadpool_posix/Thread.hpp>
#include <threadpool_posix/ThreadPool.hpp>
#include <Singleton/Singleton_normal.hpp>

namespace threadpool {

class WorkerThread: public Thread
{
public:
    WorkerThread();
    virtual ~WorkerThread();

    virtual void run();

    static void cleanup(void* ptr);
};

}