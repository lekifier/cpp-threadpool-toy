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

        virtual void run() = 0;

        void start();
        void stop();

        void set_task(Task* task);
        Task* get_task();

    protected:
        static void* thread_func(void* arg);
    protected:
        pthread_t m_thread_id;
        Task* m_task;
        Mutex m_mutex;
        Condition m_cond;
};

}