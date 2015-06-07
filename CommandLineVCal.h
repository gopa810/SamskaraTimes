// CommandLineVCal.h: interface for the CCommandLineVCal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDLINEVCAL_H__2DF20853_3345_4798_B1BE_C24A2A2C656E__INCLUDED_)
#define AFX_COMMANDLINEVCAL_H__2DF20853_3345_4798_B1BE_C24A2A2C656E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "level_0.h"
#include "platform.h"
// PORTABLE

class CCommandLineVCal : public CCommandLineInfo  
{
public:
	int GetArg_Interval(const char * pszText, int &A, int &B);
	int GetArg_Paksa(const char *  str);
	int GetArg_Date(const char *  str, VCTIME &vc);
	int GetArg_VaisnDate(const char *  str, VATIME &vc);
	int GetArg_Tithi(const char *  str);
	int GetArg_TimeZone(const char *  str, double &TimeZone);
	int GetArg_Time(const char *  str, VCTIME & vc);
	int GetArg_EarthPos(const char *  str, double &, double &);
	int MasaIndexToInternal(int nMasa);
	int GetArg_Masa(const char *  str);
	int GetArg_Int(const char *  str, int &nInteger);
	int GetArg_Year(const char *  str, int &nYear);
	int SetArgLastError(int i);
	int GetArgLastError();
	int gnLastError;
	CCommandLineVCal();
	virtual ~CCommandLineVCal();

};

#endif // !defined(AFX_COMMANDLINEVCAL_H__2DF20853_3345_4798_B1BE_C24A2A2C656E__INCLUDED_)
