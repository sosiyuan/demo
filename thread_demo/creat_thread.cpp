#include <thread>
#include <cstdio>
#include "creat_thread.h"
class background_task
{
public:
    void operator()() const
    {
        do_something();
        do_something_else();
    }

    static void do_something() { printf("%s\r\n", __FUNCTION__); }
    static void do_something_else() { printf("%s\r\n", __FUNCTION__); }
};


void demo::CreatThread()
{
    // 变量定义1 —— 传入对象
    background_task f;
    std::thread my_thread1(f);

    // 变量定义2 —— 多组括号
    std::thread my_thread2((background_task()));

    // 函数声明语句，x
    std::thread my_thread2_err(background_task());

    // 变量定义2 —— 初始化语法
    std::thread my_thread3{background_task()};

    // 变量定义3 —— lambda表达式
    std::thread my_thread([]{
        background_task::do_something();
        background_task::do_something_else(); 
    });

}