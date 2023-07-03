#include <threadpool_posix/Task.hpp>


threadpool::Task::Task()
    : m_data(NULL)
{
}

threadpool::Task::Task(void* data)
    : m_data(data)
{
}

threadpool::Task::~Task()
{
}

void* threadpool::Task::get_data()
{
    AutoLock lock(&m_mtx);
    return m_data;
}

void threadpool::Task::set_data(void* data)
{
    AutoLock lock(&m_mtx);
    m_data = data;
}