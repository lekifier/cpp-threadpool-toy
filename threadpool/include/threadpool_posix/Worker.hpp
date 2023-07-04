#pragma once
#include <threadpool_posix/Task.hpp>
#include <threadpool_posix/Thread.hpp>

namespace threadpool{
class Worker: public Thread{
protected:
    Worker(){};
public:
    virtual void set_task(Task* task){};
    virtual void run(){};
};
}