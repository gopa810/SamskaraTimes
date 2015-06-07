#include "stdafx.h"
#include "GCSankranti.h"
#include "gmath.h"
#include "GCAyanamsha.h"
#include "GCSunData.h"

GCSankranti::GCSankranti(void)
{
}


GCSankranti::~GCSankranti(void)
{
}


//==================================================================
//
//==================================================================

int gSanType = 2;


//==================================================================
//
//==================================================================

int GCSankranti::GetSankrantiType(void)
{
	return gSanType;
}

//==================================================================
//
//==================================================================

int GCSankranti::SetSankrantiType(int i)
{
	int prev = gSanType;
	gSanType = i;
	return prev;
}

//==================================================================
//
//==================================================================



const char * GCSankranti::GetSankMethodName(int i)
{
	static char * snam[] = {
		"midnight to midnight",
		"sunrise to sunrise",
		"noon to noon",
		"sunset to sunset"};

	return snam[i];
}


/*********************************************************************/
/*  Finds next time when rasi is changed                             */
/*                                                                   */
/*  startDate - starting date and time, timezone member must be valid */
/*  zodiac [out] - found zodiac sign into which is changed           */
/*                                                                   */
/*********************************************************************/

VCTIME GCSankranti::GetNextSankranti( VCTIME startDate, int &zodiac)
{
	VCTIME d;
	double step = 1.0;
	int count = 0;
	double ld, prev;
	int prev_rasi, new_rasi;
	VCTIME prevday;

	d = startDate;
	//d.ChangeTimeZone(0.0);
	//d.shour = 0.0;

	prev = put_in_360( SUNDATA::GetSunLongitude(d) - GCAyanamsha::GetAyanamsa(d.GetJulian()));
	prev_rasi = (int)floor(prev / 30.0);

	while(count < 20)
	{
		prevday = d;
		d.shour += step;
		if (d.shour > 1.0)
		{
			d.shour -= 1.0;
			d.NextDay();
		}
		
		ld = put_in_360(SUNDATA::GetSunLongitude(d) - GCAyanamsha::GetAyanamsa(d.GetJulian()));
		new_rasi = (int)floor(ld/30.0);

		if (prev_rasi != new_rasi)
		{
			zodiac = new_rasi;
			//v uplynulom dni je sankranti
			step *= 0.5;
			d = prevday;
			count++;
			continue;
		}
	}

	return d;
}
