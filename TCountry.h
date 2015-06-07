// TCountry.h: interface for the TCountry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCOUNTRY_H__35338704_92BC_4042_8A59_B567DDC356DE__INCLUDED_)
#define AFX_TCOUNTRY_H__35338704_92BC_4042_8A59_B567DDC356DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PORTABLE
#include "TStringStorage.h"

class TCountry  
{
public:
	static int SetCountryName(int nSelected, const char * psz);
	static int AddCountry(LPCTSTR pszCode, LPCTSTR pszName, int nContinent);
	static int _modified;
	static int SaveToFile(const char * szFile);
	static const char *  gcontinents[];
	static TCountry gcountries_int[];
	static TCountry gcountries_var[512];
	static int g_countries_var_count;
	static TStringStorage gcountstr;
	static const char * GetCountryAcronymByIndex(int nIndex);
	static const char * GetCountryNameByIndex(int nIndex);
	static int GetCountryCount();
	static int GetCountryCountInt();
	static const char * GetCountryContinentName(WORD w);
	static const char * GetCountryContinentNameByIndex(int nIndex);
	static const char * GetCountryName(WORD w);
	static int InitWithFile(const char * strFile);
	
	const char * pszAcr;
	short unsigned int code;
	const char * pszName;
	unsigned char continent;

};

#endif // !defined(AFX_TCOUNTRY_H__35338704_92BC_4042_8A59_B567DDC356DE__INCLUDED_)
