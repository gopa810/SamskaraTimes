#include "stdafx.h"
#include "GCTithi.h"
#include "GCMoonData.h"
#include "GCSunData.h"
#include "GCDayData.h"
#include "gmath.h"

GCTithi::GCTithi(void)
{
}


GCTithi::~GCTithi(void)
{
}

/*********************************************************************/
/*                                                                   */
/*   finds next time when starts next tithi                          */
/*                                                                   */
/*   timezone is not changed                                         */
/*                                                                   */
/*   return value: index of tithi 0..29                              */
/*                 or -1 if failed                                   */
/*********************************************************************/

int GCTithi::GetNextTithiStart(EARTHDATA ed, VCTIME startDate, VCTIME &nextDate)
{
	double phi = 12.0;
	double l1, l2, sunl;
	double jday = startDate.GetJulianComplete();
	double xj;
	MOONDATA moon;
	VCTIME d = startDate;
	VCTIME xd;
	double scan_step = 0.5;
	int prev_tit = 0;
	int new_tit = -1;

	moon.Calculate(jday, ed);
	sunl = SUNDATA::GetSunLongitude(d);
//	SunPosition(d, ed, sun, d.shour - 0.5 + d.tzone/24.0);
	l1 = put_in_360(moon.longitude_deg - sunl - 180.0);
	prev_tit = int(floor(l1/phi));

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
		//SunPosition(d, ed, sun, d.shour - 0.5 + d.tzone/24.0);
		//l2 = put_in_360(moon.longitude_deg - sun.longitude_deg - 180.0);
		sunl = SUNDATA::GetSunLongitude(d);
		l2 = put_in_360(moon.longitude_deg - sunl - 180.0);
		new_tit = int(floor(l2/phi));

		if (prev_tit != new_tit)
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
//	nextDate.shour += startDate.tzone / 24.0;
//	nextDate.NormalizeValues();
	return new_tit;
}

/*********************************************************************/
/*                                                                   */
/*   finds previous time when starts next tithi                      */
/*                                                                   */
/*   timezone is not changed                                         */
/*                                                                   */
/*   return value: index of tithi 0..29                              */
/*                 or -1 if failed                                   */
/*********************************************************************/

int GCTithi::GetPrevTithiStart(EARTHDATA ed, VCTIME startDate, VCTIME &nextDate)
{
	double phi = 12.0;
	double l1, l2, sunl;
	double jday = startDate.GetJulianComplete();
	double xj;
	MOONDATA moon;
	VCTIME d = startDate;
	VCTIME xd;
	double scan_step = 0.5;
	int prev_tit = 0;
	int new_tit = -1;

	moon.Calculate(jday, ed);
	sunl = SUNDATA::GetSunLongitude(d);
	l1 = put_in_360(moon.longitude_deg - sunl - 180.0);
	prev_tit = int(floor(l1/phi));

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
		sunl = SUNDATA::GetSunLongitude(d);
		l2 = put_in_360(moon.longitude_deg - sunl - 180.0);
		new_tit = int(floor(l2/phi));

		if (prev_tit != new_tit)
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
//	nextDate.shour += startDate.tzone / 24.0;
//	nextDate.NormalizeValues();
	return new_tit;
}

/*

Routines for calculation begining and ending times of given Tithi

Main function is GetTithiTimes

*/

double GCTithi::GetTithiTimes(EARTHDATA ed, VCTIME vc, double &titBeg, double &titEnd, double sunRise)
{
	VCTIME d1, d2;

	vc.shour = sunRise;
	GCTithi::GetPrevTithiStart(ed, vc, d1);
	GCTithi::GetNextTithiStart(ed, vc, d2);

	titBeg = d1.shour + d1.GetJulian() - vc.GetJulian();
	titEnd = d2.shour + d2.GetJulian() - vc.GetJulian();

	return (titEnd - titBeg);
}

/*********************************************************************/
/* Finds starting and ending time for given tithi                    */
/*                                                                   */
/* tithi is specified by Gaurabda year, masa, paksa and tithi number */
/*      nGYear - 0..9999                                             */
/*       nMasa - 0..12, 0-Madhusudana, 1-Trivikrama, 2-Vamana        */
/*                      3-Sridhara, 4-Hrsikesa, 5-Padmanabha         */
/*                      6-Damodara, 7-Kesava, 8-narayana, 9-Madhava  */
/*                      10-Govinda, 11-Visnu, 12-PurusottamaAdhika   */
/*       nPaksa -       0-Krsna, 1-Gaura                             */
/*       nTithi - 0..14                                              */
/*       earth  - used timezone                                      */
/*                                                                   */
/*********************************************************************/

VCTIME GCTithi::CalcTithiEnd(int nGYear, int nMasa, int nPaksa, int nTithi, EARTHDATA earth, VCTIME & endTithi)
{
	VCTIME d;

	d = DAYDATA::GetFirstDayOfYear(earth, nGYear + 1486);
	d.shour = 0.5;
	d.tzone = earth.tzone;

	return CalcTithiEndEx(d, nGYear, nMasa, nPaksa, nTithi, earth, endTithi);
}

VCTIME GCTithi::CalcTithiEndEx(VCTIME vcStart, int GYear, int nMasa, int nPaksa, int nTithi, EARTHDATA earth, VCTIME & endTithi)
{
	int i, gy, nType;
	VCTIME d, dtemp;
	DAYDATA day;
	int tithi;
	int counter;
	VCTIME start, end;
//	SUNDATA sun;
//	MOONDATA moon;
	double sunrise;
	start.shour = -1.0;
	end.shour = -1.0;
	start.day = start.month = start.year = -1;
	end.day = end.month = end.year = -1;

/*	d = GetFirstDayOfYear(earth, nGYear + 1486);
	d.shour = 0.5;
	d.TimeZone = earth.tzone;
*/
	d = vcStart;

	i = 0;
	do
	{
		d += 13;
		day.DayCalc(d, earth);
		day.nMasa = day.MasaCalc(d, earth);
		gy = day.nGaurabdaYear;
		i++;
	}
	while(((day.nPaksa != nPaksa) || (day.nMasa != nMasa)) && (i <= 30));

	if (i >= 30)
	{
		d.year = d.month = d.day = -1;
		return d;
	}

	// we found masa and paksa
	// now we have to find tithi
	tithi = nTithi + nPaksa*15;

	if (day.nTithi == tithi)
	{
		// loc1
		// find tithi juncts in this day and according to that times,
		// look in previous or next day for end and start of this tithi
		nType = 1;
	}
	else
	{
		if (day.nTithi < tithi)
		{
			// do increment of date until nTithi == tithi
			//   but if nTithi > tithi
			//       then do decrement of date
			counter = 0;
			while(counter < 30)
			{
				d.NextDay();
				day.DayCalc(d, earth);
				if (day.nTithi == tithi)
					goto cont_2;
				if ((day.nTithi < tithi ) && (day.nPaksa != nPaksa))
				{
					d.PreviousDay();
					goto cont_2;
				}
				if (day.nTithi > tithi)
				{
					d.PreviousDay();
					goto cont_2;
				}
				counter++;
			}
			// somewhere is error
			d.year = d.month = d.day = 0;
			nType = 0;
		}
		else
		{
			// do decrement of date until nTithi <= tithi
			counter = 0;
			while(counter < 30)
			{
				d.PreviousDay();
				day.DayCalc(d, earth);
				if (day.nTithi == tithi)
					goto cont_2;
				if ((day.nTithi > tithi ) && (day.nPaksa != nPaksa))
				{
					goto cont_2;
				}
				if (day.nTithi < tithi)
				{
					goto cont_2;
				}
				counter++;
			}
			// somewhere is error
			d.year = d.month = d.day = 0;
			nType = 0;

		}
cont_2:
		if (day.nTithi == tithi)
		{
			// do the same as in loc1
			nType = 1;
		}
		else 
		{
			// nTithi != tithi and nTithi < tithi
			// but on next day is nTithi > tithi
			// that means we will find start and the end of tithi
			// in this very day or on next day before sunrise
			nType = 2;
		}

	}

	// now we know the type of day-accurancy
	// nType = 0 means, that we dont found a day
	// nType = 1 means, we find day, when tithi was present at sunrise
	// nType = 2 means, we found day, when tithi started after sunrise
	//                  but ended before next sunrise
	//
	sunrise = day.sun.sunrise_deg / 360 + earth.tzone/24;

	if (nType == 1)
	{
		VCTIME d1, d2;
		d.shour = sunrise;
		GCTithi::GetPrevTithiStart(earth, d, d1);
		//d = d1;
		//d.shour += 0.02;
		GCTithi::GetNextTithiStart(earth, d, d2);

		endTithi = d2;
		return d1;
	}
	else if (nType == 2)
	{
		VCTIME d1, d2;
		d.shour = sunrise;
		GCTithi::GetNextTithiStart(earth, d, d1);
		d = d1;
		d.shour += 0.1;
		d.NormalizeValues();
		GCTithi::GetNextTithiStart(earth, d, d2);

		endTithi = d2;
		return d1;
	}

	// if nType == 0, then this algoritmus has some failure
	if (nType == 0)
	{
		d.year = 0;
		d.month = 0;
		d.day = 0;
		d.shour = 0.0;
		endTithi = d;
	}
	else
	{
		d = start;
		endTithi = end;
	}

	return d;
}


/*********************************************************************/
/*  Calculates Date of given Tithi                                   */
/*********************************************************************/

VCTIME GCTithi::CalcTithiDate(int nGYear, int nMasa, int nPaksa, int nTithi, EARTHDATA earth)
{
	int i = 0, gy = 0;
	VCTIME d, dtemp;
	DAYDATA day;
	int tithi = 0;
	int counter = 0;
	unsigned int tmp = 0;

	if (nGYear >= 464 && nGYear < 572)
	{
		tmp = DAYDATA::gGaurBeg[(nGYear-464)*26 + nMasa*2 + nPaksa];
		d.month = (tmp & 0x3e0) >> 5;
		d.day   = (tmp & 0x1f);
		d.year  = (tmp & 0xfffc00) >> 10;
		d.tzone = earth.tzone;
		d.NextDay();

		day.DayCalc(d, earth);
		day.nMasa = day.MasaCalc(d, earth);
		gy = day.nGaurabdaYear;
	}
	else
	{
		//d = GetFirstDayOfYear(earth, nGYear + 1486);
		d.day = 15;
		d.month = 2 + nMasa;
		d.year = nGYear + 1486;
		if (d.month > 12)
		{
			d.month -= 12;
			d.year++;
		}
		d.shour = 0.5;
		d.tzone = earth.tzone;

		i = 0;
		do
		{
			d += 13;
			day.DayCalc(d, earth);
			day.nMasa = day.MasaCalc(d, earth);
			gy = day.nGaurabdaYear;
			i++;
		}
		while(((day.nPaksa != nPaksa) || (day.nMasa != nMasa)) && (i <= 30));
	}

	if (i >= 30)
	{
		d.year = d.month = d.day = -1;
		return d;
	}

	// we found masa and paksa
	// now we have to find tithi
	tithi = nTithi + nPaksa*15;

	if (day.nTithi == tithi)
	{
		// loc1
		// find tithi juncts in this day and according to that times,
		// look in previous or next day for end and start of this tithi
		d.PreviousDay();
		day.DayCalc(d, earth);
		if ((day.nTithi > tithi ) && (day.nPaksa != nPaksa))
		{
			d.NextDay();
		}
		return d;
	}

	if (day.nTithi < tithi)
	{
		// do increment of date until nTithi == tithi
		//   but if nTithi > tithi
		//       then do decrement of date
		counter = 0;
		while(counter < 16)
		{
			d.NextDay();
			day.DayCalc(d, earth);
			if (day.nTithi == tithi)
				return d;
			if ((day.nTithi < tithi ) && (day.nPaksa != nPaksa))
				return d;
			if (day.nTithi > tithi)
				return d;
			counter++;
		}
		// somewhere is error
		d.year = d.month = d.day = 0;
		return d;
	}
	else
	{
		// do decrement of date until nTithi <= tithi
		counter = 0;
		while(counter < 16)
		{
			d.PreviousDay();
			day.DayCalc(d, earth);
			if (day.nTithi == tithi)
				return d;
			if ((day.nTithi > tithi ) && (day.nPaksa != nPaksa))
			{
				d.NextDay();
				return d;
			}
			if (day.nTithi < tithi)
			{
				d.NextDay();
				return d;
			}
			counter++;
		}
		// somewhere is error
		d.year = d.month = d.day = 0;
		return d;
	}

	// now we know the type of day-accurancy
	// nType = 0 means, that we dont found a day
	// nType = 1 means, we find day, when tithi was present at sunrise
	// nType = 2 means, we found day, when tithi started after sunrise
	//                  but ended before next sunrise
	//

	return d;
}

