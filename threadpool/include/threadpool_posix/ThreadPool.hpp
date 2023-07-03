#pragma once

#include <set>
#include <threadpool_posix/WorkerThread.hpp>
#include <threadpool_posix/Thread.hpp>
#include <threadpool_posix/Mutex.hpp>
#include <threadpool_posix/Condition.hpp>
#include <threadpool_posix/Task.hpp>

namespace threadpool {

class ThreadPool
{
public:
    ThreadPool();
    ~ThreadPool();

    void create(int num);

    Thread* get_idle_thread();
    void move_to_idle_list(Thread* thread);
    void move_to_busy_list(Thread* thread);

    int get_idle_thread_num();
    int get_busy_thread_num();

    void assign_task(Task* task);
private:
    int m_threads_num;
    std::set<Thread*> m_idle_list;
    std::set<Thread*> m_busy_list;

    Mutex m_idle_mutex;
    Mutex m_busy_mutex;

    Condition m_busy_cond;
    Condition m_idle_cond;
};

}
