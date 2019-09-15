/*************************************************************************
  > File Name: main.c
  > Author: skybosi
  > Mail: skybosi@163.com 
  > Created Time: 2019-09-14 09:32:44
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"master_fork.h"

#define PID_FILENAME "./nginx_simulator.pid"
#define appname "nginx_simulator"

void usage() {
    printf("usage:\n");
    printf("  -s     loading configure.\n");
    printf("  -c     create worker count.\n");
    printf("  -?/-h  show help.\n\n");
}

pid_t readPidFile(void)
{
    FILE *pid_fp = NULL;
    const char *f = PID_FILENAME;
    pid_t pid = -1;
    int i;
    if (f == NULL)
    {
        fprintf(stderr, "%s: error: no pid file name defined\n", appname);
        exit(1);
    }
    pid_fp = fopen(f, "r");
    if (pid_fp != NULL)
    {
        pid = 0;
        if (fscanf(pid_fp, "%d", &i) == 1)
            pid = (pid_t)i;
        fclose(pid_fp);
    }
    else
    {
        if (errno != ENOENT)
        {
            fprintf(stderr, "%s: error: could not read pid file\n", appname);
            fprintf(stderr, "\t%s: %s\n", f, strerror(errno));
            exit(1);
        }
    }
    return pid;
}

void writePidFile(void)
{
    FILE *fp;
    const char *f = PID_FILENAME;
    fp = fopen(f, "w+");
    if (!fp)
    {
        fprintf(stderr, "could not write pid file '%s': %s\n", f, strerror(errno));
        return;
    }
    fprintf(fp, "%d\n", (int)getpid());
    fclose(fp);
}

int checkrun(void)
{
    pid_t pid;
    pid = readPidFile();
    if (pid < 2)
        return 0;
    if (kill(pid, 0) < 0)
        return 0;
    fprintf(stderr, "nginx_master is already running!  process id %ld\n", (long int)pid);
    return 1;
}

void enable_coredumps(void)
{
    /* Set Linux DUMPABLE flag */
	if (prctl(PR_SET_DUMPABLE, 1, 0, 0, 0) != 0)
		fprintf(stderr, "prctl: %s\n", strerror(errno));
    /* Make sure coredumps are not limited */
    struct rlimit rlim;
    if (getrlimit(RLIMIT_CORE, &rlim) == 0)
    {
        rlim.rlim_cur = rlim.rlim_max;
        if (setrlimit(RLIMIT_CORE, &rlim) == 0)
        {
            fprintf(stderr, "Enable Core Dumps OK!\n");
            return;
        }
    }
    fprintf(stderr, "Enable Core Dump failed: %s\n", strerror(errno));
}

void sig_handler(int sig_num)
{
    printf("Catch signal number : %d\n",sig_num);
}

int main(int argc, char** argv)
{
    int ch;
    if (checkrun())
        exit(1);
    if (argc < 2) {
        usage();
        exit(-1);
    }
    // 开启coredumps
    enable_coredumps();
    // printf("optind:%d，opterr：%d\n", optind, opterr);
    int count = 0;
    while ((ch = getopt(argc, argv, "hs:c:")) != -1)
    {
        // printf("optind: [%c][%d]\n", ch, optind);
        switch (ch)
        {
        case 'c':
            printf("loading configure is %s\n", optarg);
            count = atoi(optarg);
            master_fork(count);
            break;
        case 's':
            printf("create worker count is %s\n", optarg);
            break;
        case 'h':
            usage();
            break;
        }
    }
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigprocmask(SIG_BLOCK,&set,NULL);
    sigemptyset(&set);
    signal(SIGINT,sig_handler);
    writePidFile();
    while(1){
        sigsuspend(&set);
        printf("Master, ctl+c is pressed!\n");
    }
    return 0;
}

