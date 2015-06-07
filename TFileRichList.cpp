// TFileRichList.cpp: implementation of the TFileRichList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFileRichList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/* BEGIN GCAL 1.4.3 */

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TFileRichList::TFileRichList()
{

}

TFileRichList::~TFileRichList()
{

}


int TFileRichList::ReadLine()
{
	int rc = 0;
	int size = 0;
	char * p;
	char * s;

	// prvotna inicializacia
	m_nFieldCount = 0;
	m_szLine[0] = 0;

	if (feof(m_fHandle))
		return 0;

	// nacitanie riadku
	while(rc = fgetc(m_fHandle))
	{
		if (feof(m_fHandle))
		{
			if (size == 0)
				return 0;
			m_szLine[size] = 0;
			break;
		}
		if (rc==10 || rc==13)
		{
			m_szLine[size]=0;
			break;
		}
		if (size < TFRL_LINESIZE-1)
		{
			m_szLine[size] = rc;
			size++;
		}
		else
		{
			m_szLine[size] = 0;
		}
	}

	// analyza riadku
	p = m_szLine;
	while(*p && isdigit(*p))
	{
		p++;
	}

	// ak je nieco za cislom
	if (*p != 0)
	{
		*p = 0;
		p++;
		while(*p && isspace(*p))
		{
			p++;
		}
		if (*p == 0)
			return 1;
		m_pFields[m_nFieldCount]=p;
		m_nFieldCount++;
		while(*p)
		{
			if (*p == '\\')
			{
				p++;
			}
			else if (*p=='|')
			{
				*p = 0;
				m_pFields[m_nFieldCount]=p+1;
				m_nFieldCount++;
			}
			p++;
		}

		// uprava fieldov
		for(int i = 0; i < m_nFieldCount; i++)
		{
			p = s = m_pFields[i];
			while(*p)
			{
				if (*p == '\\')
					p++;
				*s = *p;
				s++;
				p++;
			}
			*s = *p;
		}
	}

	return 1;
}

const char * TFileRichList::GetTag()
{
	return m_szLine;
}

const char * TFileRichList::GetField(int i)
{
	if (i<0 || i>=m_nFieldCount)
		return "";
	return m_pFields[i];
}

void TFileRichList::Clear()
{
	m_szLine[0] = 0;
	m_nFieldCount = 0;
}

int TFileRichList::AddInt(int i)
{
	sprintf(m_szTemp, "%d", i);
	return AddText(m_szTemp);
}

int TFileRichList::AddTag(int nTag)
{
	sprintf(m_szLine, "%d ", nTag);
	m_nLineTop = strlen(m_szLine);
	return m_nLineTop;
}

int TFileRichList::AddReal(double d)
{
	sprintf(m_szTemp, "%f", d);
	return AddText(m_szTemp);
}

int TFileRichList::AddText(const char *szText)
{
	int cnt = 0;
	if (m_nFieldCount > 0)
		AddChar('|');
	const char * p = szText;
	while(*p)
	{
		if (*p=='\\')
		{
			cnt++;
			AddChar('\\');
			AddChar('\\');
		}
		else if (*p=='|')
		{
			cnt++;
			AddChar('\\');
			AddChar('|');
		}
		else
			AddChar(*p);
		p++;
		cnt++;
	}
	m_nFieldCount++;
	return cnt;
}

void TFileRichList::AddChar(char c)
{
	if (m_nLineTop < TFRL_LINESIZE-1)
	{
		m_szLine[m_nLineTop] = c;
		m_nLineTop++;
		m_szLine[m_nLineTop] = 0;
	}
}

int TFileRichList::WriteLine()
{
	fprintf(m_fHandle, "%s\n", m_szLine);
	return 1;
}
