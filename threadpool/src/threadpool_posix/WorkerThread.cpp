#include <threadpool_posix/WorkerThread.hpp>

// TODO test remove base constructor
threadpool::WorkerThread::WorkerThread():Thread()
{
}

threadpool::WorkerThread::~WorkerThread()
{
}

void threadpool::WorkerThread::cleanup(void* ptr){

}

void threadpool::WorkerThread::run()
{
    sigset_t mask;
    if(sigfillset(&mask) == -1)
    {
        std::cout << "sigfillset error" << std::endl;
    }

    if(pthread_sigmask(SIG_SETMASK, &mask, NULL) == -1)
    {
        std::cout << "pthread_sigmask error" << std::endl;
    }
    pthread_cleanup_push(cleanup, this);
    while(true)
    {
        m_mutex.lock();
        while(m_task == NULL)
            m_cond.wait(m_mutex);
        m_mutex.unlock();

        int rc = 0;
        int old_state = 0;
        rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old_state);

        m_task->run();
        m_task->destory();
        m_task = NULL;

        utils::Singleton<ThreadPool>::Inst()->move_to_idle_list(this);

        rc = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state);
        pthread_testcancel();
    }
    pthread_cleanup_pop(1);
}