#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
class GetNumInstr
{
	public:
		GetNumInstr(string TestStr) :NumInstr(TestStr),fNum(0.0),iNum(0){}
		GetNumInstr() :NumInstr(""),fNum(0.0),iNum(0){}
		~GetNumInstr(){}
		GetNumInstr operator=(const string& instr);
		void outStr(){cout << NumInstr << endl;}
		GetNumInstr GetNum();
	private:
		string NumInstr;
		float fNum;
		int iNum;
};
int main()
{
	GetNumInstr num_str;
	string numStr = "qw12312q.1we122.1312asdfas";
	num_str = numStr;
	num_str.outStr();
	num_str.GetNum();
	num_str.outStr();
	//	numstr.GetNum();
	return 0;
}
GetNumInstr GetNumInstr::operator=(const string& instr)
{
	this->NumInstr = instr;
	return *this;
}
GetNumInstr GetNumInstr::GetNum()
{
	int dot = 0;
	char* str = (char*)this->NumInstr.c_str(); 
	string tmp;
	while(*str)
	{
		if((*str > '0' && *str < '9') || *str == '.') 
			tmp += *str;
		else
			tmp += ' ';
		str++;
	}
	this->NumInstr = tmp;
	return *this;
	//	sscanf(this->NumInstr.c_str(),"%*[^0-9.]%s%[^0-9.]",&tmp);
}
