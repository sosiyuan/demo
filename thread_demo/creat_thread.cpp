#include <thread>
#include <cstdio>
#include <windows.h>
#include <utility>
#include <stdexcept>
#include "creat_thread.h"
#include "public_class.h"

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

// RAII方式控制线程运行模式1 —— 引用线程对象
class thread_guard_reference : public DeleteCopyBase
{
    std::thread &t;

public:
    explicit thread_guard_reference(std::thread &t_) : t(t_)
    {
        if (!t.joinable())
        {
            throw std::logic_error("No thread");
        }
    }
    ~thread_guard_reference()
    {
        if (t.joinable())
        {
#if defined(THREAD_MODULE) && (THREAD_MODULE == JOIN_MODE)
            t.join();
#else
            t.detach();
#endif
        }
    }

};

// RAII方式控制线程运行模式1 —— 线程移动
class thread_guard_move : public DeleteCopyBase
{
    std::thread t;

public:
    explicit thread_guard_move(std::thread t_) : t(std::move(t_))
    {
        if (!t.joinable())
        {
            throw std::logic_error("No thread");
        }
    }
    ~thread_guard_move()
    {
        if (t.joinable())
        {
#if defined(THREAD_MODULE) && (THREAD_MODULE == JOIN_MODE)
            t.join();
#else
            t.detach();
#endif
        }
    }
};

/**
 * @brief 创建线程
 *
 */
void demo::CreatThread()
{
    // 变量定义1 —— 传入函数对象
    background_task f;
    std::thread my_thread1(f);
    thread_guard_reference my_thread_gurad1(my_thread1);

    // 变量定义2 —— 多组括号（传入临时函数对象，自动调用std::move）
    std::thread my_thread2((background_task()));
    thread_guard_reference my_thread_gurad2(my_thread2);

    // 函数声明语句，x
    std::thread my_thread2_err(background_task());

    // 变量定义2 —— 初始化语法
    std::thread my_thread3{background_task()};
    thread_guard_reference my_thread_gurad3(my_thread3);

    // 变量定义3 —— lambda表达式
    std::thread my_thread4([]
                           {
        background_task::do_something();
        background_task::do_something_else(); });
    thread_guard_reference my_thread_gurad4(my_thread4);

    printf("end\r\n");
}

class big_object
{
public:
    void prepare_data(int data)
    {
        m_data = data;
        printf("%s %d\r\n", __FUNCTION__, data);
    }

    void process_big_object()
    {
        while (m_data-- > 0)
        {
            printf("%s %d %p\r\n", __FUNCTION__, m_data, this);
        }
    }

private:
    int m_data;
};

/**
 * @brief 通过std::move 将参数传入线程 —— 转移变量所有权
 *
 */
void demo::ThreadParaMove()
{
    std::unique_ptr<big_object> p(new big_object);
    p->prepare_data(5);
    // move之后，转移p的所有权，原p指向nullptr
    std::thread t(big_object::process_big_object, std::move(p));
    t.join();
    return;
}

/**
 * @brief 线程所有权转移（std::move)
 *
 */
void demo::ThreadMove()
{
    std::thread t1(background_task::do_something);        // 1
    std::thread t2 = std::move(t1);                       // 2
    t1 = std::thread(background_task::do_something_else); // 3
    std::thread t3;                                       // 4
    t3 = std::move(t2);                                   // 5
    t1 = std::move(t3);                                   // 6 赋值操作将使程序崩溃
}