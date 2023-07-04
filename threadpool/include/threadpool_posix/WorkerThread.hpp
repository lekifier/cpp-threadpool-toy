#pragma once

#include <iostream>
#include <signal.h>
#include <pthread.h>
#include <threadpool_posix/Task.hpp>
#include <threadpool_posix/Mutex.hpp>
#include <threadpool_posix/Worker.hpp>
#include <threadpool_posix/Condition.hpp>
#include <threadpool_posix/ThreadPool.hpp>
#include <Singleton/Singleton_normal.hpp>


namespace threadpool {

class WorkerThread: public Worker
{
public:
    WorkerThread();
    virtual ~WorkerThread();

    virtual void run();

    static void cleanup(void* ptr);
    void set_task(Task* task);

private:
    Task* m_task;
    Mutex m_mutex;
    Condition m_cond;
};

}