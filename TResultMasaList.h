// TResultMasaList.h: interface for the TResultMasaList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRESULTMASALIST_H__E9122038_3961_4E97_BD85_1428DAA643C4__INCLUDED_)
#define AFX_TRESULTMASALIST_H__E9122038_3961_4E97_BD85_1428DAA643C4__INCLUDED_

#include "LocationRef.h"	// Added by ClassView
#include "level_0.h"	// Added by ClassView
#include "platform.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PORTABLE

class TResultMasaList  
{
public:
	int n_allocated;
	Boolean alloc(int nCountYears);
	class TResultMasa
	{
	public:
		int masa;
		int year;
		VCTIME vc_start;
		VCTIME vc_end;
	};
	TResultMasa * arr;
	VCTIME vc_end;
	VCTIME vc_start;
	int n_countYears;
	int n_countMasa;
	int n_startYear;
	CLocationRef m_location;
	TResultMasaList();
	virtual ~TResultMasaList();

};

#endif // !defined(AFX_TRESULTMASALIST_H__E9122038_3961_4E97_BD85_1428DAA643C4__INCLUDED_)
