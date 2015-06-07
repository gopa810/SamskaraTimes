// CustomEvent.h: interface for the CCustomEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMEVENT_H__BDEA8D48_FABB_4E56_BB2C_F21F3C2FB071__INCLUDED_)
#define AFX_CUSTOMEVENT_H__BDEA8D48_FABB_4E56_BB2C_F21F3C2FB071__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "platform.h"
// PORTABLE

//==============================================================
//
//==============================================================

class CCustomEvent  
{
public:
	CCustomEvent * findMasa(int nMasa);
	CCustomEvent * findNextMasa();
	CCustomEvent * findNextInMasa();
	CCustomEvent();
	virtual ~CCustomEvent();

	int nTithi;
	int nMasa;
	int nClass;
	int nFastType;
	int nVisible;
	int nStartYear;
	short int nUsed;
	short int nDeleted;
	short int nSpec;
	TString strFastSubject;
	TString strText;
	CCustomEvent * next;
	CCustomEvent * next_in_masa;
	CCustomEvent * next_masa;
};

class CCustomEventList
{
public:
	void addEvent(int inClass, int inMasa, int inTithi, int inVisible, const char * pszFastSubject, const char *  pszText, int inFastType, int inUsed, int inStartYear);
	int setOldStyleFast(int i);
	void clear();
	CCustomEvent * list;

	CCustomEventList() { list = NULL; }
	~CCustomEventList() { clear(); };
	CCustomEvent * add(void);
};

//==============================================================
//
//==============================================================

extern CCustomEventList gCustomEventList;
extern int              gCustomEventList_Modified;

//==============================================================
//
//==============================================================

/*extern TString gCustomEventTexts[360];*/

int CustomEventListReadFile(const char * pszFile);
int CustomEventListReadFile_RL(const char * pszFile);
int CustomEventListWriteFile(const char * pszFile);
int CustomEventListWriteFile_RL(const char * pszFile);
void CustomEventListRefreshLinks();
void CustomEventList_Export();

#endif // !defined(AFX_CUSTOMEVENT_H__BDEA8D48_FABB_4E56_BB2C_F21F3C2FB071__INCLUDED_)
