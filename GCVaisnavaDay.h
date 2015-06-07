#pragma once

#include "enums.h"

#include "TString.h"
#include "GCGregorianTime.h"
#include "GCEarthData.h"
#include "GCDayData.h"
#include "GCDayHours.h"

class VAISNAVADAY
{
public:
	// date
	VCTIME date;
	// moon times
	DAYTIME moonrise;
	DAYTIME moonset;
	// astronomical data from astro-sub-layer
	DAYDATA astrodata;

	DWORD nCaturmasya;
	int nDST;
	int ksaya_day2;
	int ksaya_day1;
//	int nSpecFestival;
	FeastType nFeasting;
	void Clear();
	// data for vaisnava calculations
	TString festivals;
	FastType nFastType;
	int nMhdType;
	TString ekadasi_vrata_name;
	bool ekadasi_parana;
	double eparana_time1, eparana_time2;
	int eparana_type1, eparana_type2;
	int sankranti_zodiac;
	//double sankranti_time;
	VCTIME sankranti_day;
	bool was_ksaya;
	double ksaya_time1, ksaya_time2;
	bool is_vriddhi;
	// flag for validity
	bool fDateValid;
	bool fAstroValid;
	bool fVaisValid;

	VAISNAVADAY();
	~VAISNAVADAY();
	VAISNAVADAY &operator=(VCTIME &vc);
	VAISNAVADAY &operator=(DAYDATA &dd);
	void GetFastingSubject(TString &strFest, int &nFast, TString &strFastSubj);
	int GetLineCount();
	int GetFestivalClass(TString &str);
	bool GetTithiTimeRange(EARTHDATA earth, VCTIME &from, VCTIME &to);
	bool GetNaksatraTimeRange(EARTHDATA earth, VCTIME &from, VCTIME &to);
	bool GetNextFestival(int &i, TString &str);
	int GetHeadFestival(void);
	void GetTextEP(TString &str);
	/* BEGIN GCAL 1.4.3 */
	void GetTextA(TString &str, int bPaksa, int bNaks, int bYoga, int bFlag, int bRasi);
	void GetTextRtf(TString &str, int bPaksa, int bNaks, int bYoga, int bFlag, int bRasi);
	/* END GCAL 1.4.3 */
};

