//用sscanf匹配
#include <stdio.h>
#include <string.h>
#define MAX 1000
int instr(const char* teststr,const char key);
int matchcurves(const char* teststr,const char* decollator,char* result[3]);
int main()
{
	char str1[] = "int mainint argc,char *argv";
	char* res1[3] = {0};

	char str2[] = "main(int argc,char *argv)";
	char* res2[3] = {0};

	char str3[] = "main()";
	char* res3[3] = {0};

	char str4[] = "if(a>0)";
	char* res4[3] = {0};

	char str5[] = "while(a>0)";
	char* res5[3] = {0};

	char str6[] = "for(i = 0;i < 10; i++)";
	char* res6[3] = {0};

	matchcurves(str1,"()",res1);	
	printf("%s >\n%s\n%s\n%s\n",str1,&res1[0],&res1[1],&res1[2]);
	matchcurves(str2,"()",res2);	
	//printf("%s:\n%s\n%s\n%s\n",str1,res2[0],res2[1],res2[2]);
	matchcurves(str3,"()",res3);	
	//printf("%s:\n%s\n%s\n%s\n",str1,res3[0],res3[1],res3[2]);
	matchcurves(str4,"()",res4);	
	//printf("%s:\n%s\n%s\n%s\n",str1,res4[0],res4[1],res4[2]);
	matchcurves(str5,"()",res5);	
	//printf("%s:\n%s\n%s\n%s\n",str1,res5[0],res5[1],res5[2]);
	matchcurves(str6,"()",res6);	
	//printf("%s:\n%s\n%s\n%s\n",str1,res6[0],res6[1],res6[2]);
	return 0;
}
int matchcurves(const char* teststr,const char* decollator,char* result[3])
{
	const char* str = teststr;
	int i = 0,iok = 1;
	int j = 0,jok = 1;
	int k = 0,kok = 1;
	char before_curves[100] = {0};
	char in_curves[100] = {0};
	char after_curves[100] = {0};
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
				in_curves[j++] = *str++;
			}
			/*{
			  in_curves[j++] = *str++;
			  iok = 0;
			  jok = 0;
			  after_curves[k++] = *str++;
			  }*/
		}
		result[0] = before_curves;
		result[1] = in_curves;
		result[2] = after_curves;
	//	printf("%s:\n%s\n%s\n%s\n",teststr,before_curves,in_curves,after_curves);
		printf("%s:\n%s\n%s\n%s\n",teststr,result[0],result[1],result[2]);
		printf("\n");
		return 0;
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
