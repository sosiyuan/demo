#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>

#define MAXNUM (2)
sem_t semDownload;
pthread_t a_thread, b_thread, c_thread;
int g_phreadNum = 1;

void *func1(void *arg)
{
    // 等待信号量的值 > 0
    sem_wait(&semDownload);
    printf("============== Downloading taskType 1 ============== \n");
    Sleep(5000);
    printf("============== Finished taskType 1 ============== \n");
    g_phreadNum--;
    // 等待线程结束
    pthread_join(a_thread, NULL);
    return 0;
}

void *func2(void *arg)
{
    sem_wait(&semDownload);
    printf("============== Downloading taskType 2 ============== \n");
    Sleep(3000);
    printf("============== Finished taskType 2 ============== \n");
    g_phreadNum--;
    pthread_join(b_thread, NULL);
    return 0;
}

void *func3(void *arg)
{
    sem_wait(&semDownload);
    printf("============== Downloading taskType 3 ============== \n");
    Sleep(1000);
    printf("============== Finished taskType 3 ============== \n");
    g_phreadNum--;
    pthread_join(c_thread, NULL);
    return 0;
}

int main()
{
    // 初始化信号量
    sem_init(&semDownload, 0, 0);
    int taskTypeId;
    while (scanf("%d", &taskTypeId) != EOF)
    {
        // 输入 0, 测试程序是否能正常退出
        if (taskTypeId == 0 && g_phreadNum <= 1)
        {
            break;
        }
        else if (taskTypeId == 0)
        {
            printf("Can not quit, current running thread num is %d\n", g_phreadNum - 1);
        }
        printf("your choose Downloading taskType %d\n", taskTypeId);
        // 线程数超过 2 个则不下载
        if (g_phreadNum > MAXNUM)
        {
            printf("!!! You've reached the max number of threads !!!\n");
            continue;
        }
        // 用户选择下载 Task
        switch (taskTypeId)
        {
        case 1:
            // 创建线程 1
            pthread_create(&a_thread, NULL, func1, NULL);
            // 信号量 + 1，进而触发 func1 的任务
            sem_post(&semDownload);
            // 总线程数 + 1
            g_phreadNum++;
            break;
        case 2:
            pthread_create(&b_thread, NULL, func2, NULL);
            sem_post(&semDownload);
            g_phreadNum++;
            break;
        case 3:
            pthread_create(&c_thread, NULL, func3, NULL);
            sem_post(&semDownload);
            g_phreadNum++;
            break;
        default:
            printf("!!! error taskTypeId %d !!!\n", taskTypeId);
            break;
        }
    }
    // 销毁信号量
    sem_destroy(&semDownload);
    return 0;
}