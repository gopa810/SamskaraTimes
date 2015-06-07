#pragma once

#include "GCEarthData.h"
#include "GCGregorianTime.h"
#include "GCDayHours.h"

class MOONDATA 
{
public:
	/*// illumination (synodic) phase
	double ip;
	// age of moon
	int age;
	// distance from anomalistic phase
	double di;*/
	// latitude from nodal (draconic) phase
	double latitude_deg;
	// longitude from sidereal motion
	double longitude_deg;

	double radius; //(* lambda, beta, R *)
	double rektaszension, declination;  //(* alpha, delta *)
	double parallax;
	double elevation, azimuth;//          (* h, A *)

	MOONDATA();
	~MOONDATA();
	void Calculate(double jdate, EARTHDATA earth);
	
	static void CalcMoonTimes(EARTHDATA e, VCTIME vc, double nDaylightSavingShift, DAYTIME &rise, DAYTIME &set);
	static double MoonCalcElevation(EARTHDATA e, VCTIME vc);
	static double MoonDistance(double jdate);
	static VCTIME GetNextRise(EARTHDATA e, VCTIME vc, bool bRise);
	static int GetNextMoonRasi(EARTHDATA ed, VCTIME startDate, VCTIME &nextDate);
	
	void calc_horizontal(double date, double longitude, double latitude);
	void correct_position(double jdate, double latitude, double longitude, double height);

};

