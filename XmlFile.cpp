// XmlFile.cpp: implementation of the TFileXml class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlFile.h"
// PORTABLE
#include "GCStrings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TFileXml::TFileXml()
{

}

TFileXml::~TFileXml()
{

}

void TFileXml::write(TCHAR *p)
{
	fputs(p, fout);
}

void TFileXml::write(double d)
{
	TString s;
	s.Format("%+.5f", d);
	fputs(s, fout);
}

void TFileXml::write(int n)
{
	TString s;
	s.Format("%d", n);
	fputs(s, fout);
}

void TFileXml::write(DAYTIME dt)
{
	TString s;
	if (dt.hour >= 0)
		s.Format("%02d:%02d:%02d", dt.hour, dt.min, dt.sec);
	else
		s = "N/A";
	fputs(s, fout);
}

void TFileXml::write(TString &s)
{
	fputs(s, fout);
}

void TFileXml::write(const char * s)
{
	fputs(s, fout);
}

void TFileXml::write(VCTIME vc)
{
	TString s;
	s.Format("%d %s %d", vc.day, GCStrings::GetMonthAbreviation(vc.month), vc.year);
	fputs(s, fout);
}
