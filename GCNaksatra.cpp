#include "stdafx.h"
#include "GCNaksatra.h"
#include "GCMoonData.h"
#include "gmath.h"
#include "GCAyanamsha.h"

GCNaksatra::GCNaksatra(void)
{
}


GCNaksatra::~GCNaksatra(void)
{
}

double GCNaksatra::CalculateMidnightNaksatra(VCTIME date, EARTHDATA earth)
{
	double d;
	double jdate;
	MOONDATA moon;

	date.shour = 1.0;
	jdate = date.GetJulianDetailed();
	moon.Calculate(jdate, earth);
	d = put_in_360( moon.longitude_deg - GCAyanamsha::GetAyanamsa(jdate));
	return floor(( d * 3.0) / 40.0 );
}

/*********************************************************************/
/*                                                                   */
/*   finds next time when starts next naksatra                       */
/*                                                                   */
/*   timezone is not changed                                         */
/*                                                                   */
/*   return value: index of naksatra 0..26                           */
/*                 or -1 if failed                                   */
/*********************************************************************/

int GCNaksatra::GetNextNaksatra(EARTHDATA ed, VCTIME startDate, VCTIME &nextDate)
{
	double phi = 40.0/3.0;
	double l1, l2;
	double jday = startDate.GetJulianComplete();
	MOONDATA moon;
	VCTIME d = startDate;
	double ayanamsa = GCAyanamsha::GetAyanamsa(jday);
	double scan_step = 0.5;
	int prev_naks = 0;
	int new_naks = -1;

	double xj;
	VCTIME xd;

	moon.Calculate(jday, ed);
	l1 = put_in_360(moon.longitude_deg - ayanamsa);
	prev_naks = int(floor(l1 / phi));

	int counter = 0;
	while(counter < 20)
	{
		xj = jday;
		xd = d;

		jday += scan_step;
		d.shour += scan_step;
		if (d.shour > 1.0)
		{
			d.shour -= 1.0;
			d.NextDay();
		}

		moon.Calculate(jday, ed);
		l2 = put_in_360(moon.longitude_deg - ayanamsa);
		new_naks = int(floor(l2/phi));
		if (prev_naks != new_naks)
		{
			jday = xj;
			d = xd;
			scan_step *= 0.5;
			counter++;
			continue;
		}
		else
		{
			l1 = l2;
		}
	}
	nextDate = d;
	return new_naks;
}

/*********************************************************************/
/*                                                                   */
/*   finds previous time when starts next naksatra                   */
/*                                                                   */
/*   timezone is not changed                                         */
/*                                                                   */
/*   return value: index of naksatra 0..26                           */
/*                 or -1 if failed                                   */
/*********************************************************************/

int GCNaksatra::GetPrevNaksatra(EARTHDATA ed, VCTIME startDate, VCTIME &nextDate)
{
	double phi = 40.0/3.0;
	double l1, l2;
	double jday = startDate.GetJulianComplete();
	MOONDATA moon;
	VCTIME d = startDate;
	double ayanamsa = GCAyanamsha::GetAyanamsa(jday);
	double scan_step = 0.5;
	int prev_naks = 0;
	int new_naks = -1;

	double xj;
	VCTIME xd;

	moon.Calculate(jday, ed);
	l1 = put_in_360(moon.longitude_deg - ayanamsa);
	prev_naks = int(floor(l1/phi));

	int counter = 0;
	while(counter < 20)
	{
		xj = jday;
		xd = d;

		jday -= scan_step;
		d.shour -= scan_step;
		if (d.shour < 0.0)
		{
			d.shour += 1.0;
			d.PreviousDay();
		}

		moon.Calculate(jday, ed);
		l2 = put_in_360(moon.longitude_deg - ayanamsa);
		new_naks = int(floor(l2/phi));

		if (prev_naks != new_naks)
		{
			jday = xj;
			d = xd;
			scan_step *= 0.5;
			counter++;
			continue;
		}
		else
		{
			l1 = l2;
		}

	}

	nextDate = d;
	return new_naks;

}

