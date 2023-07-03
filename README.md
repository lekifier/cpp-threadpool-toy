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

At the initial version, the thread pool may be a little bit simple,
even buggy, but today I'm a little tired, tomorrow I will try to make it better.