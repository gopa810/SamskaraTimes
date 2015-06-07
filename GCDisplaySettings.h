#pragma once

#include "showset.h"

class GCDisplaySettings
{
protected:
	static CShowSetting gss[];

public:
	static int getCount();
	static int getCountChanged();
	static char * getSettingName(int i);
	static int getValue(int i);
	static void setValue(int i, int val);
	static void setValue(const char * pszSign, int val);
	static void readFile(const char * psz);

	GCDisplaySettings(void);
	~GCDisplaySettings(void);
};

enum GCDS {
	COREEVENTS_SUN = 52,
	COREEVENTS_TITHI = 53,
	COREEVENTS_NAKSATRA = 54,
	COREEVENTS_SANKRANTI = 55,
	COREEVENTS_CONJUNCTION = 56,
	COREEVENTS_RAHUKALAM = 57,
	COREEVENTS_YAMAGHANTI = 58,
	COREEVENTS_GULIKALAM = 59,
	COREEVENTS_MOON = 60,
	COREEVENTS_MOONRASI = 61,
	COREEVENTS_ASCENDENT = 62,
	COREEVENTS_SORT = 63
};
