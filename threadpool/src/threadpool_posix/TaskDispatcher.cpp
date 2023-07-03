#include <threadpool_posix/TaskDispatcher.hpp>

threadpool::TaskDispatcher::TaskDispatcher()
{
}

threadpool::TaskDispatcher::~TaskDispatcher()
{
}

void threadpool::TaskDispatcher::init(int thread)
{
    utils::Singleton<ThreadPool>::Inst()->create(thread);
    // std::cout << "thread pool addr: " << utils::Singleton<ThreadPool>::Inst() << std::endl;   
    // threadpool::Thread::start();
    start();
}

void threadpool::TaskDispatcher::assign_task(Task* task)
{
    m_mutex.lock();
    m_task_list.push_back(task);
    m_mutex.unlock();
    m_cond.signal();
}

void threadpool::TaskDispatcher::handle(Task* task)
{
    ThreadPool* pool = utils::Singleton<ThreadPool>::Inst();
    if(pool->get_idle_thread_num()>0) pool->assign_task(task);
    else{
        m_mutex.lock();
        m_task_list.push_back(task);
        m_mutex.unlock();
    }
    task->run();
}

void threadpool::TaskDispatcher::run()
{
    sigset_t mask;
    if(sigfillset(&mask) < 0)
    {
        std::cout << "sigfillset error" << std::endl;
        return;
    }
    if(pthread_sigmask(SIG_SETMASK, &mask, NULL) < 0)
    {
        std::cout << "pthread_sigmask error" << std::endl;
        return;
    }
    while (true)
    {
        m_mutex.lock();
        while (m_task_list.empty())
            m_cond.wait(m_mutex);
        Task* task = m_task_list.front();
        m_task_list.pop_front();
        m_mutex.unlock();
        handle(task);
    }
}