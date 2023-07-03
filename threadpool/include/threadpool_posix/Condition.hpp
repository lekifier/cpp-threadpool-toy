#pragma once

#include <time.h>
#include <pthread.h>
#include <threadpool_posix/Mutex.hpp>

namespace threadpool {

class Condition
{
public:
    Condition();
    ~Condition();

    int wait(Mutex& mutex);
    int timedwait(int seconds, Mutex& mutex);
    int signal();
    int broadcast();
protected:
    pthread_cond_t m_cond;
};

}