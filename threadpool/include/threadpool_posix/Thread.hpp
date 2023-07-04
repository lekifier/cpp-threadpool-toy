#pragma once

#include <pthread.h>
#include <threadpool_posix/Mutex.hpp>
#include <threadpool_posix/Condition.hpp>
#include <threadpool_posix/Task.hpp>

namespace threadpool {

class Thread{
    public:
        Thread();
        virtual ~Thread();
        void start();
        void stop();

        virtual void run() = 0;

    protected:
        static void* thread_func(void* arg);
    protected:
        pthread_t m_thread_id;
};

}