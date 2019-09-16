/*************************************************************************
  > File Name: sockerpair.c
  > Author: skybosi
  > Mail: skybosi@163.com 
  > Created Time: 2019-09-16 20:19:43
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXLINE 4096

int main(int argc, char **argv) {
    int fd[2];
    pid_t pid;
    char line[MAXLINE];
    int n;
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fd) < 0) {
        perror("socketpair error");
        exit(1);
    }
    if ( (pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid > 0) {
        // 子进程中 
        close(fd[1]);
        char* line = "child  say >> hello world\n";
        write(fd[0], line, strlen(line));
        char tmp[MAXLINE];
        n = read(fd[0], tmp, MAXLINE);
        write(STDOUT_FILENO, tmp, n);
    } else {
        // 父进程中
        close(fd[0]);
        n = read(fd[1], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
        char tmp[] = "parent say >> I recive: hello world\n";
        write(fd[1], tmp, strlen(tmp));
    }
    exit(0);
}
