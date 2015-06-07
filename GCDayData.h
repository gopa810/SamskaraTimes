#pragma once

#include "GCSunData.h"
#include "GCMoonData.h"

class DAYDATA
{
public:
	// date of Julian epoch
	double jdate;
	// sun
	SUNDATA sun;
	// moon
	MOONDATA moon;
	// year of Gaurabda epoch
	int nGaurabdaYear;
	// value of ayanamsa for this date
	double msAyanamsa;
	// sign of zodiac
	int nSunRasi;
	// rasi of the moon
	int nMoonRasi;
	// tithi #
	int nTithi;
	// tithi at arunodaya
	int nTithiArunodaya;
	// tithi at sunset
	int nTithiSunset;
	// tithi elaps.
	double nTithiElapse;
	// paksa
	int nPaksa;
	// yoga
	int nYoga;
	// yoga elaps.
	double nYogaElapse;
	// naksatra
	int nNaksatra;
	// naksatra elaps.
	double nNaksatraElapse;
	// masa
	int nMasa;
	// distance of moon and sun in degrees
	double msDistance;

	DAYDATA(void);


	int DayCalc(VCTIME date, EARTHDATA earth);
	int MasaCalc(VCTIME date, EARTHDATA earth);

	static unsigned int gGaurBeg[];
	static VCTIME GetFirstDayOfYear(EARTHDATA,int);
	static VCTIME GetFirstDayOfMasa(EARTHDATA earth, int GYear, int nMasa);

};


