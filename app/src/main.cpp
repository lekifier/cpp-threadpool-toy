#include <iostream>
#include <string>
#include <unistd.h>
#include <Singleton/Singleton_normal.hpp>
#include <threadpool_posix/Task.hpp>
#include <threadpool_posix/TaskDispatcher.hpp>

#include <app/EchoTask_posix.hpp>

int main() {
    int threads = 10;
    utils::Singleton<threadpool::TaskDispatcher>::Inst()->init(threads);
    for(int i=0; i<20; i++){
        int *num = new int(i);
        threadpool::Task *task = new app::EchoTask(num);
        utils::Singleton<threadpool::TaskDispatcher>::Inst()->assign_task(task);
        usleep(100);
    }
    usleep(100000000);
    return 0;
}
