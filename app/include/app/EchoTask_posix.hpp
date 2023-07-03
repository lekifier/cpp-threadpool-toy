#include <unistd.h>
#include <string>
#include <iostream>
#include <threadpool_posix/Task.hpp>

namespace app
{
    class EchoTask : public threadpool::Task
    {
    public:
        EchoTask(int *num): threadpool::Task((void*)num) {};
        virtual ~EchoTask(){};

        virtual void run() override{
            int *input = static_cast<int*>(m_data);
            std::cout << "num: " << *input << std::endl;
            usleep(1000);
        }
        virtual void destory() override{
            delete static_cast<int*>(m_data);
            delete this;
        }
    };
}