#include "hierarchical_mutex.h"

hierarchical_mutex high_level_mutex(10000); // 1
hierarchical_mutex low_level_mutex(5000);   // 2
int do_low_level_stuff() {}
int low_level_func()
{
    std::lock_guard<hierarchical_mutex> lk(low_level_mutex); // 3
    return do_low_level_stuff();
}
void high_level_stuff(int some_param) {}
void high_level_func()
{
    std::lock_guard<hierarchical_mutex> lk(high_level_mutex); // 4
    high_level_stuff(low_level_func());                       // 5
}
void thread_a() // 6-遵循层级顺序，OK
{
    high_level_func();
}

hierarchical_mutex other_mutex(100); // 7
void do_other_stuff() {}
void other_stuff()
{
    high_level_func(); // 8
    do_other_stuff();
}
void thread_b() // 9
{
    std::lock_guard<hierarchical_mutex> lk(other_mutex); // 10-违反层级顺序，抛出异常
    other_stuff();
}