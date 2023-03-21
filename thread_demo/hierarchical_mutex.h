/**
 * @file hierarchical_mutex.h
 * @author your name (you@domain.com)
 * @brief 层级互斥量
 * @version 0.1
 * @date 2023-03-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __HIERARCHICAL_MUTEX_H__
#define __HIERARCHICAL_MUTEX_H__
#include <mutex>

/* 层次结构的互斥类 */
class hierarchical_mutex
{
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value; // 1
    void check_for_hierarchy_violation()
    {
        if (this_thread_hierarchy_value <= hierarchy_value) // 2
        {
            throw std::logic_error("mutex hierarchy violated");
        }
    }
    void update_hierarchy_value()
    {
        previous_hierarchy_value = this_thread_hierarchy_value; // 3
        this_thread_hierarchy_value = hierarchy_value;
    }

public:
    explicit hierarchical_mutex(unsigned long value) : hierarchy_value(value), previous_hierarchy_value(0)
    {
    }
    void lock()
    {
        check_for_hierarchy_violation(); // 层级校验
        internal_mutex.lock();           // 4-上锁（获取锁）
        update_hierarchy_value();        // 5-更新层级数据
    }
    void unlock()
    {
        this_thread_hierarchy_value = previous_hierarchy_value; // 6-解锁时恢复层级数据
        internal_mutex.unlock();
    }
    bool try_lock()
    {
        check_for_hierarchy_violation();
        if (!internal_mutex.try_lock()) // 7
            return false;
        update_hierarchy_value();
        return true;
    }
};

thread_local unsigned long
    hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX); // 7

#endif // __HIERARCHICAL_MUTEX_H__
