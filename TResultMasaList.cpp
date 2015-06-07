// TResultMasaList.cpp: implementation of the TResultMasaList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vcal5beta.h"
#include "TResultMasaList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// PORTABLE

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// PORTABLE

TResultMasaList::TResultMasaList()
{
	n_countMasa = 0;
	n_countYears = 0;
	n_startYear = 0;
	n_allocated = 0;
	arr = NULL;
}

TResultMasaList::~TResultMasaList()
{
	if (arr != NULL)
	{
		delete [] arr;
		arr = NULL;
	}
}

Boolean TResultMasaList::alloc(int nCountYears)
{
	if (n_allocated < nCountYears)
	{
		if (arr != NULL)
			delete [] arr;
		arr = NULL;
	}
	arr = new TResultMasa[nCountYears*14];
	n_allocated = nCountYears;
	return arr ? true : false;
}
