// LocationRef.h: interface for the CLocationRef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCATIONREF_H__029EEF44_2BAC_4D6B_BAF7_E6EDC1530A98__INCLUDED_)
#define AFX_LOCATIONREF_H__029EEF44_2BAC_4D6B_BAF7_E6EDC1530A98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "level_0.h"
// PORTABLE

class CLocationRef  
{
public:
	TString m_strTimeZone;
	TString m_strLatitude;
	TString m_strLongitude;
	TString m_strName;
	TString m_strFullName;
	double  m_fLongitude;
	double  m_fLatitude;
	double  m_fTimezone;
	int     m_nDST;
	
	CLocationRef() {};
	virtual ~CLocationRef() {};
	operator EARTHDATA() {
		EARTHDATA e; 
		e.dst = m_nDST; 
		e.latitude_deg = m_fLatitude; 
		e.longitude_deg = m_fLongitude;
		e.tzone = m_fTimezone; return e;
	};
	EARTHDATA operator=(EARTHDATA e) { 
		m_fLongitude = e.longitude_deg; 
		m_fLatitude = e.latitude_deg; 
		m_fTimezone = e.tzone; 
		m_nDST = e.dst; return e;
	};
	

};

#endif // !defined(AFX_LOCATIONREF_H__029EEF44_2BAC_4D6B_BAF7_E6EDC1530A98__INCLUDED_)
