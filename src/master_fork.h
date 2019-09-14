/*************************************************************************
	> File Name: master_fork.h
	> Author: skybosi
	> Mail: skybosi@163.com 
	> Created Time: 2019-09-14 09:33:29
 ************************************************************************/

#include <stdio.h>
#include<unistd.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

typedef struct{
    // 当前worker的个数
    size_t  worker_n;
    // 当前运行的worker的pid
    pid_t*  work_pids;
} master_s;

typedef master_s* master_t;
sig_atomic_t reap;
sig_atomic_t terminate;
sig_atomic_t quit;
int exiting;

int master_fork(int count);
int worker(void* data);
void worker_process_cycle(void *data);
