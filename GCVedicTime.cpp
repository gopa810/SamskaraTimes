#include "stdafx.h"
#include "GCVedicTime.h"


VATIME::VATIME(void)
{
}

VATIME::VATIME(int t, int m, int y)
{
	tithi = t;
	masa = m;
	gyear = y; 
}

void VATIME::next()
{
	tithi++;
	if (tithi >= 30)
	{
		tithi %= 30;
		masa++;
	}
	if (masa >= 12)
	{
		masa %= 12;
		gyear++;
	}
}

void VATIME::prev()
{
	if (tithi == 0)
	{
		if (masa == 0)
		{
			masa = 11;
			tithi = 29;
		}
		else
		{
			masa--;
			tithi = 29;
		}
	}
	else
	{
		tithi--;
	}
}

