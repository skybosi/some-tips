#include <iostream>
#include <stdlib.h>
using namespace std;

class Rb
{
	public:

	Rb(){ cout << "Rb is here!" << endl;}
	~Rb(){cout << "Rb is leave" << endl;}
};

void hh()
{
	Rb rb;
	for(int i = 0; i <3 ; i++)
	{
		cout << "in hhhhhh" << endl;
	}
	throw 47;
}

int main ()
{
	try
	{

		cout << "hh is coming ......" << endl;
		hh();
//		return 0;
//		exit(0);
//		abort();
	}
	catch(int )
	{
		cout << "catch th hh's throw" << endl;
	}
	

}


