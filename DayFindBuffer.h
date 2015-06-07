// DayFindBuffer.h: interface for the CDayFindBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DAYFINDBUFFER_H__AF9C178D_F95F_4882_858F_3CCABC2BDEC9__INCLUDED_)
#define AFX_DAYFINDBUFFER_H__AF9C178D_F95F_4882_858F_3CCABC2BDEC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "level_5_days.h"
#include "level_0.h"	// Added by ClassView
// PORTABLE

class TFinderBuffer : public TResultCalendar  
{
public:
	int GetUpperBound();
	int GetStartIndex();
	int CalculateFindCalendar(int start_year, int start_month, EARTHDATA earth, int DST);
	VAISNAVADAY m_rData[50];
	TFinderBuffer();
	virtual ~TFinderBuffer();

};

#endif // !defined(AFX_DAYFINDBUFFER_H__AF9C178D_F95F_4882_858F_3CCABC2BDEC9__INCLUDED_)
