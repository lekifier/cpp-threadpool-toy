#include<threadpool_posix/Condition.hpp>

using namespace threadpool;

Condition::Condition()
{
    pthread_cond_init(&m_cond, NULL);
}

Condition::~Condition()
{
    pthread_cond_destroy(&m_cond);
}

int Condition::wait(Mutex& mutex)
{
    return pthread_cond_wait(&m_cond, &mutex.m_mutex);
}

int Condition::timedwait(int seconds, Mutex& mutex)
{
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += seconds;
    return pthread_cond_timedwait(&m_cond, &mutex.m_mutex, &abstime);
}

int Condition::signal()
{
    return pthread_cond_signal(&m_cond);
}

int Condition::broadcast()
{
    return pthread_cond_broadcast(&m_cond);
}