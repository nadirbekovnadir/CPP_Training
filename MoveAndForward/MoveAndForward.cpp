// MoveAndForward.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "MoveAndForward.h"

class A
{
public:
    A() {};

    int g;

    A(A&& aa) noexcept 
    {
        std::cout << "Move!\n";
    }

    A(const A& aa) noexcept
    {
        std::cout << "Copy!\n";
    }
};

template<class T>
void wrapper(T&& t) {
    A b(forward<T>(t));
}

template<class T>
void std_wrapper(T&& t) {
    A b(std::forward<T>(t));
}

int main()
{
    //std::shared_ptr<int> p = factory<int>(5);

    // forward<A>(A());

    // const A cc;
    // my_forward(cc);

    A ccc;

    A a;
    A b(forward<A>(a));
    A d(forward<A>(A()));

    std::cout << std::endl;

    wrapper(a);
    // std_wrapper(a);
    wrapper(A());
    
    // a.g = 5;

    // A c(a);

    int i = 0;

    //move(A());

    std::cout << "Hello World!\n";
}
