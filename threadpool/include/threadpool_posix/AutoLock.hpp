#pragma once
#include <threadpool_posix/Mutex.hpp>
namespace threadpool {

class AutoLock
{
public:
    AutoLock(Mutex* mutex);
    ~AutoLock();
private:
    Mutex* m_mutex;
};

}