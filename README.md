# Cpp multi-thread practice with thread pool toy
There are so many content in Cpp multi-thread develop
 - posix & c++11 thread
 - thread life cycle
 - comunication between threads

I want to practice it with a toy project, and this toy project is 
inspired by [yazi](https://github.com/yespon/yazi) awesome project.
Thanks for his great work, by the way, there are many other great 
components which I'll "fork" to my project.

At initial version, this project is almost the same as the project
I mentioned above, but I will try to add more features to it:
maybe a event driven dispatcher, maybe a machinisim 
to avoid spin lock, maybe a lock free queue...

Besides, I try to use CMake to build this project, and I will try to
use CTest to do unit test (maybe).

## Project structure
'threadpool' folder is the core module, and 'app' folder is an example
using this theadpool components.

When using these components, user need to define a class derived from 
task, which has two virtual functions to override: run() and destroy().
run() is the function to be executed by thread, and destroy() is the
function to release the resource of task.

Besides, user should declare a TaskDispatcher object, which is a Singleton
class actually, and call its init() function to do initialization.
The init() function will create a thread pool, and start a dispatcher thread,
after that, user can call assign() function to assign a task to dispather.
Dispatcher will dispatch the task to a worker thread if there is any idle 
worker thread, or put the task into a queue if all worker threads are busy.
## Object profiles
As mentioned above, there are two main Singleton objects: TaskDispatcher and
ThreadPool. And there are two main kinds of objects: WorkerThread and Task.
WorkerThread will work on the task assigned by TaskDispatcher.

TaskDispatcher is actually a thread too, it maintains a queue of tasks, perform
as a buffer between user and worker threads.

ThreadPool is a container of WorkerThread, it will create a number of WorkerThread
when it is initialized, and maintain two list: idle list and busy list.

WorkerThread is a thread, same as TaskDispatcher, so I made a base class named Thread,
and WorkerThread and TaskDispatcher are both derived from it. However, because we
need move busy worker thread to idle list when the task is done, so the worker thread
need to access the ThreadPool singleton instance or we need to do some communication work
bewteen worker thread and thread pool that will be a performance degradation, 
and the ThreadPool also need to accessthe worker thread to assign 
a task to it, so there is a circular reference between them.

To avoid this, I made a class named Worker, which is the inter layer between Thread and
WorkerThread. So when we can create a pointer of Worker which points to a WorkerThread,
and manipulate the WorkerThread through the Worker pointer. If there is no inter layer,
we declare a pointer of WorkerThread, because of the circular reference, the compile work
will fail.

## Time Line

[2023-07-03] Thread pool may be a little bit simple, even buggy, 
but today I'm a little tired, tomorrow I will try to make it better.

[2023-07-04] Thread class is more abstract now, WorkerThread and Dispatcher
are both derived from it.

## TODO
- [ ] summerize the thread life cycle (Resource Management)
- [ ] summerize the thread communication (LOCKS Wrangling)
- [ ] c11 thread style support