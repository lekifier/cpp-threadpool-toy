#pragma once
#include <pthread.h>
#include <signal.h>
#include <iostream>
#include <list>

#include <threadpool_posix/Task.hpp>
#include <threadpool_posix/Mutex.hpp>
#include <threadpool_posix/Condition.hpp>
#include <threadpool_posix/Thread.hpp>
#include <threadpool_posix/ThreadPool.hpp>

#include <Singleton/Singleton_normal.hpp>

namespace threadpool {

class TaskDispatcher: public Thread
{
public:
    TaskDispatcher();
    ~TaskDispatcher();

    void init(int thread);
    void assign_task(Task* task);
    void handle(Task* task);
    virtual void run();

protected:
    std::list<Task*> m_task_list;
    Mutex m_mutex;
    Condition m_cond;
};

}