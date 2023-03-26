#include "signal_demo.h"
#include <iostream>
#include <thread>
#include <mutex>

namespace ThreadSafeByStaticConstract
{
#define MODE 3
    std::mutex SingletonLock;

    // 线程安全 —— 静态创建对象
    struct StaticClassDemo
    {
        StaticClassDemo()
        {
            std::cout << "StaticClassDemo: " << this << std::endl;
        }
        ~StaticClassDemo()
        {
            std::cout << "~StaticClassDemo: " << this << std::endl;
        }
        static StaticClassDemo *GetInstance()
        {
#if defined(MODE) && MODE == 1
            // 非线程安全
            if (p == nullptr)
            {
                p = new StaticClassDemo();
            }
            return p;
#elif defined(MODE) && MODE == 2
            // 线程安全 —— 双重检查锁
            if (p == nullptr)
            {
                std::lock_guard<std::mutex> lg(SingletonLock);
                if (p == nullptr)
                {
                    p = new StaticClassDemo();
                }
            }
            return p;
#else
            // 静态创建型单例模式
            // 静态变量的构造函数、析构函数是线程安全的
            static StaticClassDemo s_StaticClassDemo;
            return &s_StaticClassDemo;
#endif
        }

    private:
        static StaticClassDemo *p;
    };
    StaticClassDemo *StaticClassDemo::p = nullptr;

    sem_t TestStaticSem;

    void TestStatic()
    {
        StaticClassDemo *pStaticClassDemo = StaticClassDemo::GetInstance();
        sem_wait(&TestStaticSem);
        std::cout << "TestStatic:" << pStaticClassDemo << std::endl;
        sem_post(&TestStaticSem);
    }

    void DemoMain()
    {
        sem_init(&TestStaticSem, 0, 0);
        std::thread t1(TestStatic);
        std::thread t2(TestStatic);
        std::thread t3(TestStatic);
        std::thread t4(TestStatic);
        std::thread t5(TestStatic);

        sem_post(&TestStaticSem);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        std::cout << "Hello World" << std::endl;
        sem_destroy(&TestStaticSem);
    }
}; // namespace ThreadSafeByStaticConstract

static struct RegDemoFuncS
{
    RegDemoFuncS()
    {
        RegDemoFunc()(ThreadSafeByStaticConstract::DemoMain);
        // RegDemoFunc()(SemDemo);
    }
} s_regDemoFunc;
