// SimpleDataFile.cpp: implementation of the TFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// PORTABLE

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TFile::TFile()
{
	m_cend = -1;
}

TFile::~TFile()
{

}

int TFile::Open(const char * szname, const char *mode)
{
	m_fHandle = fopen(szname, mode);
	return (m_fHandle == NULL ? 0 : 1);
}

void TFile::Close()
{
	if (m_fHandle)
		fclose(m_fHandle);
}

char TFile::m_szLine[TFLL];

BOOL TFile::ReadString2(TString &strA, TString &strB)
{
	if (ReadString(strA) == FALSE)
		return FALSE;
	if (ReadString(strB) == FALSE)
		return FALSE;
	strB.TrimRight();
	return TRUE;
}

BOOL TFile::WriteString2(int i, double a)
{
	TString str;
	str.Format("%d\r\n%f\r\n", i, a);
	WriteString(str);
	return TRUE;
}

BOOL TFile::WriteString2(int i, int n)
{
	TString str;
	str.Format("%d\r\n%d\r\n", i, n);
	WriteString(str);
	return TRUE;
}

BOOL TFile::WriteString2(int i, const char * psz)
{
	TString str;
	str.Format("%d\r\n%s\r\n", i, psz);
	WriteString(str);
	return TRUE;
}

int TFile::ReadPropertyLine(TString &strA, TString &strB)
{
	BOOL bVal = FALSE;
	UINT rd = 0;
	char ch;

	strA.Empty();
	strB.Empty();

	while(ch = getc(m_fHandle), !feof(m_fHandle))
	{

		rd ++;

		if (ch == '=')
		{
			bVal = TRUE;
		}
		else if ((ch == 0x0a) || (ch == 0x0d))
		{
			if (rd > 1)
				return 1;
		}
		else if (bVal == TRUE)
		{
			strB += ch;
		}
		else
		{
			strA += ch;
		}

	}

	return feof(m_fHandle) ? 0 : 1;
}

//========================================================================
// return values
//  0 - end of file or error
//  > 0 - read string

int TFile::ReadString(TString &str)
{
	int rp;

	if (feof(m_fHandle))
		return 0;

	str = "";

	while(rp = fgetc(m_fHandle), !feof(m_fHandle))
	{
		if (rp == 0x0a || rp == 0x0d)
		{
			if (m_cend == -1)
				m_cend = rp;
			if (m_cend == rp)
				break;
		}
		else
		{
			str += char(rp);
		}
	}

	if (feof(m_fHandle))
		return 0;

	return str.GetLength();
}

//=======================================================================
// return values
//  nonzero - success
//  EOF     - error of end of file

int TFile::WriteString(const char *str)
{
	return fputs(str, m_fHandle);
}
