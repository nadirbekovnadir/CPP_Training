#pragma once

#define DEBUG

#include <memory>

template <class T, class A1>
std::shared_ptr<T> factory(A1&& a1)   // версия с одним аргументом
{
    return std::shared_ptr<T>(new T(std::forward(a1)));
}

template<class T> struct remove_reference
{
    typedef T type;
};

template<class T> struct remove_reference<T&>
{
    typedef T type;
};

template<class T> struct remove_reference<T&&>
{
    typedef T type;
};

template<class T>
typename remove_reference<T>::type&& move(T&& _Arg)
{
    return (static_cast<typename remove_reference<T>::type&&>(_Arg));
}

template<class T>
T&& forward(typename remove_reference<T>::type& t) noexcept 
{
#ifdef DEBUG
    std::cout << "forward(T& t)\n";
#endif // DEBUG

    return static_cast<T&&>(t);
}

template<class T>
constexpr T&& forward(std::remove_reference_t<T>&& t) noexcept
{
#ifdef DEBUG
    std::cout << "forward(T&& t)\n";
#endif // DEBUG

    return static_cast<T&&>(t);
}

template <typename T>
decltype(auto) my_forward(T&& arg) // universal reference (can be rvalue- or lvalue-reference)
{
    return static_cast<T&&>(arg);
    // T&& can be expanded to:
    // Foo& && - gives us Foo&
    // const Foo& && - give us const Foo&
    // Foo && - gives us Foo&&
    // const Foo && - gives us const Foo&&
}
