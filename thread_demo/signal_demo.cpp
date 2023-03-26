#include "signal_demo.h"
#include <iostream>
extern void SignalDemo();

static struct RegDemoFuncS
{
    RegDemoFuncS()
    {
        RegDemoFunc()(SemDemo);
    }
} s_regDemoFunc;

void SignalDemo()
{
    std::cout << "Hello World" << std::endl;
}