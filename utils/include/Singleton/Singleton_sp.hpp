#pragma once
#include<memory>

namespace utils{

template <typename T>
class Singleton_sp{
private:
    Singleton_sp() = default;
    Singleton_sp(const Singleton_sp&) = delete;
    Singleton_sp& operator=(const Singleton_sp&) = delete;
    static std::unique_ptr<T> instance;
public:
    static T& Inst(){
        return instance;
    }
};

template<typename T>
std::unique_ptr<T> Singleton_sp<T>::instance = std::make_unique<T>();
}