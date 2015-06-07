// TStringStorage.cpp: implementation of the TStringStorage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vcal5beta.h"
#include "TStringStorage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TStringStorage::TStringStorage()
{

}

TStringStorage::~TStringStorage()
{
	TStringStoragePage * P = pages.next;
	TStringStoragePage * R = NULL;

	while(P)
	{
		R = P;
		P = P->next;
		delete R;
	}
}

const char * TStringStorage::add(const char *pString)
{
	int L;
	char * S = NULL;
	TStringStoragePage * P = &pages;

	while(P)
	{
		L = strlen(pString);
		if (P->top < 1023 - L)
		{
			S = (char *)(P->sz + P->top);
			strcpy(S, pString);
			S[L] = 0;
			P->top += L + 1;
			return S;
		}
		if (P->next == NULL)
		{
			P->next = new TStringStoragePage;
			if (P->next == NULL)
				return NULL;
		}
		P = P->next;
	}

	return NULL;
}
