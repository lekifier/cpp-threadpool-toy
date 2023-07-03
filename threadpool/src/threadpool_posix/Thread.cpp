#include <threadpool_posix/AutoLock.hpp>
#include <threadpool_posix/Thread.hpp>

threadpool::Thread::Thread()
    : m_thread_id(0), m_task(NULL)
{
}

threadpool::Thread::~Thread()
{
}

void threadpool::Thread::start()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&m_thread_id, &attr, thread_func, (void*)this);
    pthread_attr_destroy(&attr);
}

void threadpool::Thread::stop()
{
    pthread_exit(PTHREAD_CANCELED);
}

void* threadpool::Thread::thread_func(void* arg)
{
    Thread* thread = (Thread*)arg;
    thread->run();
    return NULL;
}

void threadpool::Thread::set_task(Task* task)
{
    AutoLock lock(&m_mutex);
    m_task = task;
    m_cond.signal();
}

threadpool::Task* threadpool::Thread::get_task()
{
    AutoLock lock(&m_mutex);
    return m_task;
}