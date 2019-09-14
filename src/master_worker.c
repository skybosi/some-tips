/*************************************************************************
	> File Name: worker.c
	> Author: skybosi
	> Mail: skybosi@163.com 
	> Created Time: 2019-09-14 12:28:42
 ************************************************************************/

#include<stdio.h>
#include"master_fork.h"
void worker_process_init(int worker)
{
}

void worker_process_exit(void)
{
}

void worker_process_cycle(void *data)
{
    int worker = (intptr_t)data;
    worker_process_init(worker);
    for (;;)
    {
        if (exiting)
        {
            fprintf(stderr, "exiting");
            worker_process_exit();
        }
        fprintf(stderr, "At Work [Master] (%d) worker cycle pid: %d\n", getppid(), getpid());
        sleep(3);
        if (terminate)
        {
            fprintf(stderr, "exiting");
            worker_process_exit();
        }
        if (quit)
        {
            quit = 0;
            fprintf(stderr, "gracefully shutting down");
            if (!exiting)
            {
                exiting = 1;
            }
        }
    }
}
