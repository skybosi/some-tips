#include<stdio.h>
int main()
{
	long playtimes = 1113;
	char Cplaytimes[10] = {0};
	sprintf(Cplaytimes,"%ld",playtimes);
	printf ("[%s]\n",Cplaytimes);
	return 0;
}
