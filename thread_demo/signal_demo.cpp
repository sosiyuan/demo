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
            // 存在条件竞争，会导致未定义的结果
            if (p == nullptr)
            {
                p = new StaticClassDemo();
            }
            return p;
#elif defined(MODE) && MODE == 2
            // 线程安全 —— 双重检查锁
            // 存在条件竞争，会导致未定义的结果
            if (p == nullptr)
            {
                std::lock_guard<std::mutex> lg(SingletonLock);
                if (p == nullptr)
                {
                    p = new StaticClassDemo();
                }
            }
            return p;
#elif defined(MODE) && MODE == 3
            // C++标准库 —— call_once; 消耗的资源比互斥锁少
            // 延时初始化，不存在条件竞争
            void (*pFunc)() = []
            {
                if (p == nullptr)
                {
                    p = new StaticClassDemo();
                }
            };
            std::call_once(singletonInitFlag, pFunc);
            return p;
#else
            // 静态创建型单例模式
            // c++11 标准下 静态变量的构造函数、析构函数是线程安全的
            static StaticClassDemo s_StaticClassDemo;
            return &s_StaticClassDemo;
#endif
        }

    private:
        static StaticClassDemo *p;
        static std::once_flag singletonInitFlag;
    };
    std::once_flag StaticClassDemo::singletonInitFlag;
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

// REG_DEMO_FUNC(ThreadSafeByStaticConstract::DemoMain);
