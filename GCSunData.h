#pragma once

#include "GCDayHours.h"
#include "GCGregorianTime.h"
#include "GCEarthData.h"
#include "enums.h"

class SUNDATA
{
public:
	double length_deg;
	double arunodaya_deg;
	double sunrise_deg;
	double sunset_deg;

	double declination_deg;
	double longitude_deg;
	double longitude_set_deg;
	double longitude_arun_deg;
	double right_asc_deg;

	// time of arunodaya - 96 mins before sunrise
	DAYTIME arunodaya;
	// time of sunrise
	DAYTIME rise;
	// time of noon
	DAYTIME noon;
	// time of sunset
	DAYTIME set;
	// length of the day
	DAYTIME length;

	SUNDATA(void);
	static double GetSunLongitude(VCTIME vct);
	static double SunGetPerigee(int year, int month, int day);
	static double SunGetMeanLong(int year, int month, int day);
	
	void SunPosition(VCTIME vct, EARTHDATA ed, double dayHours);
	void SunCalc(VCTIME vct, EARTHDATA earth);

	static void CalculateKala(double sunRise, double sunSet, int dayWeek, double * r1, double * r2, KalaType kt);
};


