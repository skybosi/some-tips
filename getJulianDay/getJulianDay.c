#include <stdio.h>
long GetJulianDay(int Year, int Month, int Day);
int main()
{
	int Y = 2015;
	int M = 10;
	int D = 10;
	long JD = GetJulianDay(Y,M,D);
	printf("julianday = %ld\n",JD);
	return 0;
}
long GetJulianDay(int Year, int Month, int Day)
{
	long y = (long) Year;
	long m = (long) Month;
	long d = (long) Day;
	if (m > 2) 
		m = m - 3;
	else 
	{
		m = m + 9;
		y = y - 1;
	}
	long c = y / 100;
	long ya = y - 100 * c;
	long j = (146097L * c) / 4 + (1461L * ya) / 4 + (153L * m + 2) / 5 + d + 1721119L;
	return j;
}
