#ifndef _MY_MATH_IMP_H
#define _MY_MATH_IMP_H 1

#include <iostream>

class MyMath
{
public:
    template <class T>
    T add(T a, T b)
    {
        return a + b;
    }
    ~MyMath()
    {
        std::cout << "death " << this << std::endl;
    }

protected:
private:
};

#endif