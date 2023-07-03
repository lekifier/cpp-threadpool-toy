#include <threadpool_posix/ThreadPool.hpp>
#include <iostream>

threadpool::ThreadPool::ThreadPool():m_threads_num(0)
{
}

threadpool::ThreadPool::~ThreadPool()
{
}

void threadpool::ThreadPool::create(int num)
{
    AutoLock lock(&m_idle_mutex);
    m_threads_num = num;
    for(int i = 0; i < num; i++)
    {
        WorkerThread* thread = new WorkerThread();
        m_idle_list.insert(thread);
        thread->start();
    }
}

threadpool::Thread* threadpool::ThreadPool::get_idle_thread()
{
    AutoLock lock(&m_idle_mutex);
    while(m_idle_list.empty())
        m_idle_cond.wait(m_idle_mutex);
    return *m_idle_list.begin();
}

void threadpool::ThreadPool::move_to_idle_list(Thread* thread)
{
    m_idle_mutex.lock();
    m_idle_list.insert(thread);
    m_idle_cond.signal();
    m_idle_mutex.unlock();

    m_busy_mutex.lock();
    std::set<Thread*>::iterator it = m_busy_list.find(thread);
    if(it != m_busy_list.end())
        m_busy_list.erase(it);
    m_busy_cond.signal();
    m_busy_mutex.unlock();
}

void threadpool::ThreadPool::move_to_busy_list(Thread* thread)
{
    m_busy_mutex.lock();
    while(m_busy_list.size() == m_threads_num)
        m_idle_cond.wait(m_idle_mutex);
    m_busy_list.insert(thread);
    m_busy_mutex.unlock();

    m_idle_mutex.lock();
    std::set<Thread*>::iterator it = m_idle_list.find(thread);
    if(it != m_idle_list.end())
        m_idle_list.erase(it);
    m_idle_mutex.unlock();
}

int threadpool::ThreadPool::get_idle_thread_num()
{
    AutoLock lock(&m_idle_mutex);
    return m_idle_list.size();
}

int threadpool::ThreadPool::get_busy_thread_num()
{
    AutoLock lock(&m_busy_mutex);
    return m_busy_list.size();
}

void threadpool::ThreadPool::assign_task(Task* task)
{
    if(task==NULL) return;
    Thread* thread = get_idle_thread();

    if(thread != NULL)
    {
        move_to_busy_list(thread);
        thread->set_task(task);
    }
    else
    {
        std::cout << "thraed is null" << std::endl;
    }   
}