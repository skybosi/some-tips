#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
using namespace std;

int main()
{
	/*stringstream  ost;
	int c = 122232;
	string a = "hello";
	ost << c/1000 <<"."<< c%1000 << a;
	cout << "hhhhhh:"<< ost.str() << endl;*/
	long a = 0;
	char ch[32];
	string b = "4e20";
	sscanf(b.c_str(),"%x",&a);
	sprintf(ch,"%ld",a);
	cout << a << endl;
	cout << ch << endl;
	return 0;
}
