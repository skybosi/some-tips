/*************************************************************************
  > File Name: write2fd.c
  > Author: skybosi
  > Mail: skybosi@163.com 
  > Created Time: 2019-09-16 07:55:30
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define SIZE 100
int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Usage%s fd\n", argv[0]);
        exit(-1);
    }
	int fd = atoi(argv[1]);
	int count = 0;
	char data[SIZE];
	printf("请输入字符串\n");
	scanf("%s", &data);
	count = strlen(data);
	if (write(fd, data, count) == -1) {
		printf("write data fail\n");
		return 0;
	}
	return 0;
}
