#ifndef __PUBLIC_H__
#define __PUBLIC_H__
#include "stdexcept"

using DEMO_FUNC_TYPE = void (*)();
extern DEMO_FUNC_TYPE g_demoFunc;

struct RegDemoFunc
{
    void operator()(DEMO_FUNC_TYPE pFunc)
    {
        if (!g_demoFunc)
        {
            g_demoFunc = pFunc;
        }
        else
        {
            throw std::logic_error("Repeat DemoFunc");
        }
    }
};

#define REG_DEMO_FUNC(p)       \
    static struct RegDemoFuncS \
    {                          \
        RegDemoFuncS()         \
        {                      \
            RegDemoFunc()(p);  \
        }                      \
    } s_regDemoFunc;
#endif // __PUBLIC_H__
