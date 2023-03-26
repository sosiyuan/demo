#include "public.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>
#include "creat_thread.h"

DEMO_FUNC_TYPE g_demoFunc = nullptr;

int main()
{
    // demo::CreatThread();

    // demo::ThreadParaMove();
    if(g_demoFunc){
        (*g_demoFunc)();
    }

    return 0;
}