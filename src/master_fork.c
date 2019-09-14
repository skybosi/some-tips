/*************************************************************************
  > File Name: master_fork.c
  > Author: skybosi
  > Mail: skybosi@163.com 
  > Created Time: 2019-09-14 09:35:47
 ************************************************************************/

#include<sys/types.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<wait.h>
#include<errno.h>
#include<stdlib.h>
#include<errno.h>
#include"master_fork.h"

static master_s g_master_s;

int master_fork(int count)
{
	printf("master_fork count: %d pid: %d\n", count, getpid());
    pid_t pid, w;
    int status;
    for (int i=1; i <= count; i++)
    {
        pid = fork();
        if (pid < 0) {
			printf("[Worker]: Fork failed!\n");
			exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
			printf("At Worker [Master]: (%d) created worker(%d). \n", getppid(), getpid());
			g_master_s.worker_n++;
			g_master_s.work_pids = &pid;
			g_master_s.work_pids++;
            prctl(PR_SET_NAME, worker_name);
            worker_process_cycle((void*)&g_master_s);
            /*
            char* argv[] = { "worker_simulator", NULL };
            if(-1 == execvp("./worker_simulator", argv)){
                perror("execvp failed");
            }
            exit(0);
            */
            break;
        }
        else {
			// printf("At Master [Master]: (%d) created worker(%d). \n", getppid(), getpid());
            // break;
			// do {
			// 	w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
			// 	if (w == -1) {
			// 		perror("waitpid");
			// 		exit(EXIT_FAILURE);
			// 	}
			// 	if (WIFEXITED(status)) {
			// 		printf("exited, status = %d\n", WEXITSTATUS(status));
			// 	} else if (WIFSIGNALED(status)) {
			// 		printf("killed by signal %d\n", WTERMSIG(status));
			// 	} else if (WIFSTOPPED(status)) {
			// 		printf("stopped by signal %d\n", WSTOPSIG(status));
			// 	} else if (WIFCONTINUED(status)) {
			// 		printf("continued\n");
			// 	}
			// } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            // exit(EXIT_SUCCESS);
        }
    }
/*
	while(i++ < count) {
		pid = fork();
		switch(pid){
		case -1:
			printf("[Worker]: Fork failed!\n");
			exit(EXIT_FAILURE);
            break;
		case 0:
			// printf("[Master]: (%d) created worker(%d). \n", getppid(), getpid());
            break;
		default:
			// printf("[Worker]: Master(%d) Fork worker(%d) \n", getppid(), getpid());
			g_master_s.worker_n++;
			g_master_s.work_pids = &pid;
			g_master_s.work_pids++;
			// do {
			// 	w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
			// 	if (w == -1) {
			// 		perror("waitpid");
			// 		exit(EXIT_FAILURE);
			// 	}
			// 	if (WIFEXITED(status)) {
			// 		printf("exited, status = %d\n", WEXITSTATUS(status));
			// 	} else if (WIFSIGNALED(status)) {
			// 		printf("killed by signal %d\n", WTERMSIG(status));
			// 	} else if (WIFSTOPPED(status)) {
			// 		printf("stopped by signal %d\n", WSTOPSIG(status));
			// 	} else if (WIFCONTINUED(status)) {
			// 		printf("continued\n");
			// 	}
			// } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            // exit(EXIT_SUCCESS);
			break;
		}
	}
*/
	// printf("[Worker]: Master(%d) Fork worker(%d) \n", getppid(), getpid());
	return 0;
}

