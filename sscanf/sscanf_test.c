#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAx 100

int instr(const char* teststr,const char key);
int matchcurves(const char* teststr,const char* decollator,char* result[3]);
void matchfree(char* result[3]);
int main()
{

	//char str[] = "int main(\"int argc,char** argv\")";
	char str[] = " main()";
	char* res[3] = {0};
	matchcurves(str,"()",res);	
	printf("%s >\n%s\n%s\n%s\n",str,res[0],res[1],res[2]);
	matchfree(res);
	return 0;
}
int matchcurves(const char* teststr,const char* decollator,char* result[3])
{
	const char* str = teststr;
	int i = 0,iok = 1;
	int j = 0,jok = 1;
	int k = 0,kok = 1;
	//	char before_curves[10] = {0};
	//	char in_curves[100] = {0};
	//	char after_curves[100] = {0};
	char* before_curves = calloc(10,sizeof(char*));
	char* in_curves = calloc(100,sizeof(char*));
	char* after_curves = calloc(100,sizeof(char*));
	if(instr(teststr,'('))
	{
		while(*str)
		{
			if(*str != decollator[0] && iok)
			{
				before_curves[i++] = *str++;
			}
			else if(*str != decollator[1] && jok)
			{
				iok = 0;
				in_curves[j++] = *str++;
			}
			else
			{
				if(jok)
				{
					jok = 0;
					in_curves[j] = *str++;
				}
				after_curves[k++] = *str++;
			}
		}
		result[0] = before_curves;
		result[1] = in_curves;
		result[2] = after_curves;
		printf("%s:\n1:%s\n2:%s\n3:%s\n",teststr,result[0],result[1],result[2]);
		return 1;
	}
	printf("no key!\n");
	return 0;
}
int instr(const char* teststr,const char key)
{
	while(*teststr)
		if(*teststr++ == key)
			return 1;
	return 0;
}
void matchfree(char* result[])
{
	int i = 0;
	while(i < 3)
		free(result[i++]);
}
