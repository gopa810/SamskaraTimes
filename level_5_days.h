// PORTABLE
// level_5_days.h: interface for the TResultCalendar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEVEL_5_DAYS_H__957DEA2E_87AF_4C5B_A359_4E0C8F511234__INCLUDED_)
#define AFX_LEVEL_5_DAYS_H__957DEA2E_87AF_4C5B_A359_4E0C8F511234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "level_0.h"
#include "LocationRef.h"
;
#define CDB_MAXDAYS 16
#define BEFORE_DAYS 8

class TResultCalendar  
{
public:
	VAISNAVADAY * m_pData;
	int m_nCount;
	int m_PureCount;
	CLocationRef m_Location;
	VCTIME m_vcStart;
	int m_vcCount;
public:
	void ResolveFestivalsFasting(int i);
	Boolean AddSpecFestival(VAISNAVADAY &day, int nSpecialFestival, const char * pszClass);
	CProgressCtrl * m_pProgress;
	int CalculateEParana(VAISNAVADAY &s, VAISNAVADAY &t, double &begin, double &end, EARTHDATA earth);
	int FindDate(VCTIME vc);
	Boolean IsFestivalDay(VAISNAVADAY &yesterday, VAISNAVADAY &today, int nTithi);
	VAISNAVADAY * GetDay(int nIndex);
	int MahadvadasiCalc(int nIndex, EARTHDATA earth);
	int CompleteCalc(int nIndex, EARTHDATA earth);
	int EkadasiCalc(int nIndex, EARTHDATA earth);
	int ExtendedCalc(int nIndex, EARTHDATA earth);
	int CalculateCalendar(CLocationRef & loc, VCTIME begDate, int iCount);
	Boolean IsMhd58(int nIndex, int &nMahaType);
	Boolean NextNewFullIsVriddhi(int nIndex, EARTHDATA earth);
	int nBeg;
	int nTop;
	TResultCalendar();
	virtual ~TResultCalendar();

	int top;
	VAISNAVADAY days[CDB_MAXDAYS];

	int Push(VAISNAVADAY &day);
};

#endif // !defined(AFX_LEVEL_5_DAYS_H__957DEA2E_87AF_4C5B_A359_4E0C8F511234__INCLUDED_)
