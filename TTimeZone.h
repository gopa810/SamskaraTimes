// TTimeZone.h: interface for the TTimeZone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TTIMEZONE_H__B0EA8616_6B27_46C9_B778_0E2C7F07858C__INCLUDED_)
#define AFX_TTIMEZONE_H__B0EA8616_6B27_46C9_B778_0E2C7F07858C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PORTABLE
#include "platform.h"

class VCTIME;

class TTimeZone  
{
public:
	static int ID2INDEX(int _id);
	static int GetID(const char * p);
	static int GetNormalTimeStartDate(int nDst, int nYear, VCTIME &vcStart);
	static int GetDaylightTimeStartDate(int nDst, int nYear, VCTIME &vcStart);
	static int GetTimeZoneBias(int ndst);
	static void ExportDB();
	static void ExpandVal(UInt32 dw, int a[]);
	static Boolean GetXMLString(TString &str, int nIndex);
	static int GetTimeZoneCount();
	static double GetTimeZoneOffset(int nIndex);
	static int GetTimeZoneOffsetInteger(int nIndex);
	static const char * GetTimeZoneName(int nIndex);
	static TTimeZone gzone[];
	static char * GetTimeZoneOffsetTextArg(double d);
	static char * GetTimeZoneOffsetText(double d);
	static int determineDaylightChange(VCTIME vc2, int nIndex);
	static int determineDaylightStatus(VCTIME vc, int nIndex);
	static int GetDaylightBias(VCTIME vc, DWORD val);
	static int is_n_xday(VCTIME vc, int n, int x);

	const char * name;
	int offset;
	int bias;
	unsigned long int val;
	float latA;
	float latB;
	float lonA;
	float lonB;
	int idx;

};

#endif // !defined(AFX_TTIMEZONE_H__B0EA8616_6B27_46C9_B778_0E2C7F07858C__INCLUDED_)
