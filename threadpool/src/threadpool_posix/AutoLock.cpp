#include <threadpool_posix/AutoLock.hpp>

using namespace threadpool;

AutoLock::AutoLock(Mutex* mutex)
    : m_mutex(mutex)
{
    m_mutex->lock();
}

AutoLock::~AutoLock()
{
    m_mutex->unlock();
}
