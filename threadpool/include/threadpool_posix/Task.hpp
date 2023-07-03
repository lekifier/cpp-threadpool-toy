#pragma once
#include <threadpool_posix/Mutex.hpp>
#include <threadpool_posix/AutoLock.hpp>
namespace threadpool {

class Task{
    public:
        Task();
        Task(void* data);
        virtual ~Task();

        void* get_data();
        void set_data(void* data);

        virtual void run() = 0;
        virtual void destory() = 0;

    protected:
        void* m_data;
        Mutex m_mtx;
};

}
