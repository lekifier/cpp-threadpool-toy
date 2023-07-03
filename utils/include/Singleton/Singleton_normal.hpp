#pragma once
namespace utils{

template <typename T>
class Singleton
{
    private:
        Singleton() = default;
        Singleton(const Singleton<T>&) = delete;
        Singleton<T>& operator=(const Singleton<T>&) = delete;
    public:
        static T* Inst(){
            static T* instance = new T();
            return instance;
        };
};

}