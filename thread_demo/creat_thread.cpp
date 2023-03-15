#include <thread>
#include <cstdio>
#include <windows.h>
#include "creat_thread.h"

#define JOIN_MODE 1
#define DETACH_MODE 0
#define THREAD_MODULE JOIN_MODE

class background_task
{
public:
    void operator()() const
    {
        Sleep(500);
        do_something();
        do_something_else();
    }

    static void do_something() { printf("%s\r\n", __FUNCTION__); }
    static void do_something_else() { printf("%s\r\n", __FUNCTION__); }
};

// RAII方式控制线程运行模式
class thread_guard
{
    std::thread &t;

public:
    explicit thread_guard(std::thread &t_) : t(t_) {}
    ~thread_guard()
    {
#if defined(THREAD_MODULE) && (THREAD_MODULE == JOIN_MODE)
        if (t.joinable())
        {
            t.join();
        }
#else
        t.detach();
#endif
    }
    thread_guard(thread_guard const &) = delete;
    thread_guard &operator=(thread_guard const &) = delete;
};

void demo::CreatThread()
{
    // 变量定义1 —— 传入对象
    background_task f;
    std::thread my_thread1(f);
    thread_guard my_thread_gurad1(my_thread1);

    // 变量定义2 —— 多组括号
    std::thread my_thread2((background_task()));
    thread_guard my_thread_gurad2(my_thread2);

    // 函数声明语句，x
    std::thread my_thread2_err(background_task());

    // 变量定义2 —— 初始化语法
    std::thread my_thread3{background_task()};
    thread_guard my_thread_gurad3(my_thread3);

    // 变量定义3 —— lambda表达式
    std::thread my_thread4([]{
        background_task::do_something();
        background_task::do_something_else(); });
    thread_guard my_thread_gurad4(my_thread4);

    printf("end\r\n");

}