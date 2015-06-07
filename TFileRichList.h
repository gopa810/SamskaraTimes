// TFileRichList.h: interface for the TFileRichList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TFILERICHLIST_H__51FC62F9_E3DD_4066_8848_329E97F82509__INCLUDED_)
#define AFX_TFILERICHLIST_H__51FC62F9_E3DD_4066_8848_329E97F82509__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TFile.h"
/* BEGIN GCAL 1.4.3 */

#define TFRL_LINESIZE 1024
#define TFRL_MAXFIELDS 64

class TFileRichList : public TFile  
{
public:
	int WriteLine();
	int m_nLineTop;
	void AddChar(char c);
	int AddText(const char * szText);
	int AddReal(double d);
	int AddTag(int nTag);
	char m_szTemp[64];
	int AddInt(int i);
	void Clear();
	const char * GetField(int i);
	int m_nFieldCount;
	const char * GetTag();
	char m_szLine[TFRL_LINESIZE];
	int ReadLine();
	char *m_pFields[TFRL_MAXFIELDS];
	TFileRichList();
	virtual ~TFileRichList();

};
/* END GCAL 1.4.3 */
#endif // !defined(AFX_TFILERICHLIST_H__51FC62F9_E3DD_4066_8848_329E97F82509__INCLUDED_)
