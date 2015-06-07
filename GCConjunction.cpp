#include "stdafx.h"
#include "GCConjunction.h"
#include "gmath.h"
#include "GCMoonData.h"
#include "GCSunData.h"

GCConjunction::GCConjunction(void)
{
}


GCConjunction::~GCConjunction(void)
{
}

/*********************************************************************/
/*                                                                   */
/*  m1 - previous moon position                                      */
/*  m2 - next moon position                                          */
/*  s1 - previous sun position                                       */
/*  s2 - next sun position                                           */
/*                                                                   */
/*  Test for conjunction of the sun and moon                         */
/*  m1,s1 is in one time moment                                      */
/*  m2,s2 is in second time moment                                   */
/*                                                                   */
/*  this function tests whether conjunction occurs between           */
/*  these two moments                                                */
/*                                                                   */
/*********************************************************************/

bool GCConjunction::IsConjunction(double m1, double s1, double s2, double m2)
{
	if (m2 < m1)
		m2 += 360.0;
	if (s2 < s1)
		s2 += 360.0;
	if ((m1 <= s1) && (s1 < s2) && (s2 <= m2))
		return true;

	m1 = put_in_180(m1);
	m2 = put_in_180(m2);
	s1 = put_in_180(s1);
	s2 = put_in_180(s2);

	if ((m1 <= s1) && (s1 < s2) && (s2 <= m2))
		return true;

	return false;
}

///////////////////////////////////////////////////////////////////////
// GET PREVIOUS CONJUNCTION OF THE SUN AND MOON
//
// THIS IS HELP FUNCTION FOR GetPrevConjunction(VCTIME test_date, 
//                                         VCTIME &found, bool this_day, EARTHDATA earth)
//
// looking for previous sun-moon conjunction
// it starts from input day from 12:00 AM (noon) UTC
// so output can be the same day
// if output is the same day, then conjunction occurs between 00:00 AM and noon of this day
//
// date - input / output
// earth - input
// return value - sun longitude in degs
//
// error is when return value is greater than 999.0 deg

double GCConjunction::GetPrevConjunction(VCTIME &date, EARTHDATA earth)
{
	int bCont = 32;
	double prevSun = 0.0, prevMoon = 0.0, prevDiff = 0.0;
	double nowSun = 0.0, nowMoon = 0.0, nowDiff = 0.0;
//	SUNDATA sun;
	MOONDATA moon;
	double jd;
	VCTIME d;

	d = date;
	d.shour = 0.5;
	d.tzone = 0.0;
	jd = d.GetJulian();//GetJulianDay(d.year, d.month, d.day);

	// set initial data for input day
	// NOTE: for grenwich
	//SunPosition(d, earth, sun);
	moon.Calculate(jd, earth);
	prevSun = SUNDATA::GetSunLongitude(d);
	prevMoon = moon.longitude_deg;
	prevDiff = put_in_180(prevSun - prevMoon);

	do
	{
		// shift to day before
		d.PreviousDay();
		jd -= 1.0;
		// calculation
		//SunPosition(d, earth, sun);
		moon.Calculate(jd, earth);
		nowSun = SUNDATA::GetSunLongitude(d);
		nowMoon = moon.longitude_deg;
		nowDiff = put_in_180(nowSun - nowMoon);
		// if difference of previous has another sign than now calculated
		// then it is the case that moon was faster than sun and he 
		//printf("        prevsun=%f\nprevmoon=%f\nnowsun=%f\nnowmoon=%f\n", prevSun, prevMoon, nowSun, nowMoon);


		if (IsConjunction(nowMoon, nowSun, prevSun, prevMoon))
		{
			// now it calculates actual time and zodiac of conjunction
			double x;
			if (prevDiff == nowDiff)
				return 0;
			x = fabs(nowDiff) / fabs(prevDiff - nowDiff);
			if (x < 0.5)
			{
				d.shour = x + 0.5;
			}
			else
			{
				d.NextDay();
				d.shour = x - 0.5;
			}
			date = d;
			double other = SUNDATA::GetSunLongitude(d);
//			double other2 = nowSun + (prevSun - nowSun)*x;
			put_in_360(prevSun);
			put_in_360(nowSun);
			if (fabs(prevSun - nowSun) > 10.0)
			{
				return put_in_180(nowSun) + (put_in_180(prevSun) - put_in_180(nowSun))*x;
			}
			else
				return nowSun + (prevSun - nowSun)*x;
//			return other2;
		}
		prevSun = nowSun;
		prevMoon = nowMoon;
		prevDiff = nowDiff;
		bCont --;
	}
	while(bCont >= 0);

	return 1000.0;
}

///////////////////////////////////////////////////////////////////////
// GET NEXT CONJUNCTION OF THE SUN AND MOON
//
// Help function for GetNextConjunction(VCTIME test_date, VCTIME &found, 
//                                      bool this_day, EARTHDATA earth)
//
// looking for next sun-moon conjunction
// it starts from input day from 12:00 AM (noon) UTC
// so output can be the same day
// if output is the same day, then conjunction occurs 
// between noon and midnight of this day
//
// date - input / output
// earth - input
// return value - sun longitude
//
// error is when return value is greater than 999.0 deg

double GCConjunction::GetNextConjunction(VCTIME &date, EARTHDATA earth)
{
	int bCont = 32;
	double prevSun = 0.0, prevMoon = 0.0, prevDiff = 0.0;
	double nowSun = 0.0, nowMoon = 0.0, nowDiff = 0.0;
	//SUNDATA sun;
	MOONDATA moon;
	double jd;
	VCTIME d;

	d = date;
	d.shour = 0.5;
	d.tzone = 0.0;
	jd = d.GetJulian();

	// set initial data for input day
	// NOTE: for grenwich
	//SunPosition(d, earth, sun, 0.0);
	moon.Calculate(jd, earth);
	nowSun = put_in_360(SUNDATA::GetSunLongitude(d));
	nowMoon = put_in_360(moon.longitude_deg);
	nowDiff = put_in_180(nowSun - nowMoon);

	do
	{
		// shift to day before
		d.NextDay();
		jd += 1.0;
		// calculation
		//SunPosition(d, earth, sun, 0.0);
		moon.Calculate(jd, earth);
		prevSun = SUNDATA::GetSunLongitude(d);
		prevMoon = moon.longitude_deg;
		prevDiff = put_in_180(prevSun - prevMoon);
		// if difference of previous has another sign than now calculated
		// then it is the case that moon was faster than sun and he 
		//printf("        prevsun=%f\nprevmoon=%f\nnowsun=%f\nnowmoon=%f\n", prevSun, prevMoon, nowSun, nowMoon);


		if (IsConjunction(nowMoon, nowSun, prevSun, prevMoon))
		{
			// now it calculates actual time and zodiac of conjunction
			double x;
			if (prevDiff == nowDiff)
				return 0;
			x = fabs(nowDiff) / fabs(prevDiff - nowDiff);
			if (x < 0.5)
			{
				d.PreviousDay();
				d.shour = x + 0.5;
			}
			else
			{
				d.shour = x - 0.5;
			}
			date = d;
			put_in_360(prevSun);
			put_in_360(nowSun);
			if (fabs(prevSun - nowSun) > 10.0)
			{
				return put_in_180(nowSun) + (put_in_180(prevSun) - put_in_180(nowSun))*x;
			}
			else
				return nowSun + (prevSun - nowSun)*x;
		}
		nowSun = prevSun;
		nowMoon = prevMoon;
		nowDiff = prevDiff;
		bCont --;
	}
	while(bCont >= 0);

	return 1000.0;
}

/*********************************************************************/
/*                                                                   */
/*                                                                   */
/*                                                                   */
/*                                                                   */
/*                                                                   */
/*********************************************************************/

double GCConjunction::GetPrevConjunction(VCTIME test_date, VCTIME &found, bool this_conj, EARTHDATA earth)
{
	double phi = 12.0;
	double l1, l2, sunl;

	if (this_conj)
	{
		test_date.shour -= 0.2;
		test_date.NormalizeValues();
	}

	
	double jday = test_date.GetJulianComplete();
	double xj;
	MOONDATA moon;
	VCTIME d = test_date;
	VCTIME xd;
	double scan_step = 1.0;
	int prev_tit = 0;
	int new_tit = -1;

	moon.Calculate(jday, earth);
	sunl = SUNDATA::GetSunLongitude(d);
	l1 = put_in_180(moon.longitude_deg - sunl);
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

		moon.Calculate(jday, earth);
		sunl = SUNDATA::GetSunLongitude(d);
		l2 = put_in_180(moon.longitude_deg - sunl);
		new_tit = int(floor(l2/phi));

		if (prev_tit >= 0 && new_tit < 0)
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
			prev_tit = new_tit;
		}

	}
	found = d;
	return sunl;
}

/*********************************************************************/
/*                                                                   */
/*                                                                   */
/*                                                                   */
/*                                                                   */
/*                                                                   */
/*********************************************************************/

double GCConjunction::GetNextConjunction(VCTIME test_date, VCTIME &found, bool this_conj, EARTHDATA earth)
{
	double phi = 12.0;
	double l1, l2, sunl;

	if (this_conj)
	{
		test_date.shour += 0.2;
		test_date.NormalizeValues();
	}

	
	double jday = test_date.GetJulianComplete();
	double xj;
	MOONDATA moon;
	VCTIME d = test_date;
	VCTIME xd;
	double scan_step = 1.0;
	int prev_tit = 0;
	int new_tit = -1;

	moon.Calculate(jday, earth);
	sunl = SUNDATA::GetSunLongitude(d);
	l1 = put_in_180(moon.longitude_deg - sunl);
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

		moon.Calculate(jday, earth);
		sunl = SUNDATA::GetSunLongitude(d);
		l2 = put_in_180(moon.longitude_deg - sunl);
		new_tit = int(floor(l2/phi));

		if (prev_tit < 0 && new_tit >= 0)
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

		prev_tit = new_tit;
	}
	found = d;
	return sunl;
}
