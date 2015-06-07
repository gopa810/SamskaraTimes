#ifndef _RESAPPDAY_________
#define _RESAPPDAY_________


#include "level_0.h"
#include "locationref.h"
// PORTABLE

#define TRESULT_APP_CELEBS 3

class TResultApp
{
public:
	CLocationRef location;
	VCTIME  event;
	DAYDATA details;
	Boolean b_adhika;
	int celeb_gy[TRESULT_APP_CELEBS];
	VCTIME celeb_date[TRESULT_APP_CELEBS];
};

#endif