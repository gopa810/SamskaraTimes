#include "stdafx.h"
#include "level_0.h"
#include "strings.h"
#include "enums.h"

// PORTABLE



char * AvcGetTimeZoneName(int n)
{
	char * tzn[] = {
    "UTC-12",
    "UTC-11",
    "UTC-10",
    "UTC-9:30",
    "UTC-9",
    "UTC-8",
    "UTC-7",
    "UTC-6",
    "UTC-5",
    "UTC-4:30",
    "UTC-4",
    "UTC-3:30",
    "UTC-3",
    "UTC-2",
    "UTC-1",
    "UTC",
    "UTC+1",
    "UTC+2",
    "UTC+3",
    "UTC+3:30",
    "UTC+4",
    "UTC+4:30",
    "UTC+5",
    "UTC+5:30",
    "UTC+5:45",
    "UTC+6",
    "UTC+6:30",
    "UTC+7",
    "UTC+8",
    "UTC+8:45",
    "UTC+9",
    "UTC+9:30",
	"UTC+9:45",
    "UTC+10",
    "UTC+10:30",
    "UTC+11",
    "UTC+11:30",
    "UTC+12",
    "UTC+12:45",
    "UTC+13",
    "UTC+14"
	};

	if (n < 0)
		n = 0;
	if (n > 40)
		n = 40;
	return tzn[n];
}

double AvcGetTimeZone(int nIndex)
{
	double tzval[] = {
    -12.0,
    -11.0,
    -10.0,
    -9.5,
    -9.0,
    -8.0,
    -7.0,
    -6.0,
    -5.0,
    -4.5,
    -4.0,
    -3.5,
    -3.0,
    -2.0,
    -1.0,
    +0.0,
    +1.0,
    +2.0,
    +3.0,
    +3.5,
    +4.0,
    +4.5,
    +5.0,
    +5.5,
    +5.75,
    +6.0,
    +6.5,
    +7.0,
    +8.0,
    +8.75,
    +9.0,
    +9.5,
	+9.75,
    +10.0,
    +10.5,
    +11.0,
    +11.5,
    +12.0,
    +12.75,
    +13.0,
    +14.0
	};

	if (nIndex < 0)
		nIndex = 0;
	if (nIndex > 40)
		nIndex = 40;
	return tzval[nIndex];
}

int AvcGetNearestTimeZone(double d)
{

	if (d <= AvcGetTimeZone(0))
		return 0;
	if (d >= AvcGetTimeZone(40))
		return 40;
	int n;
	for(n = 0; n < 41; n++)
	{
		if (fabs(AvcGetTimeZone(n) - d) < 0.01)
			return n;
		if ((AvcGetTimeZone(n) <= d) && (AvcGetTimeZone(n+1) >= d))
		{
			if ((d - AvcGetTimeZone(n)) < (AvcGetTimeZone(n+1) - d))
				return n;
			else
				return n+1;
		}
	}

	return 39;
}



