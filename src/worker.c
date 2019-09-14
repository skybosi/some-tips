/*************************************************************************
	> File Name: worker.c
	> Author: skybosi
	> Mail: skybosi@163.com 
	> Created Time: 2019-09-14 12:28:42
 ************************************************************************/

#include<stdio.h>
#include"master_fork.h"

int main(int argc, char* argv)
{
    for (;;)
    {
        if (exiting)
        {
            fprintf(stderr, "exiting");
        }
        fprintf(stdout, "\tworker cycle getpid: %d\n", getpid());
        sleep(1);
        if (terminate)
        {
            fprintf(stderr, "exiting");
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
    return 0;
}
