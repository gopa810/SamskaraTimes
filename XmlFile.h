// XmlFile.h: interface for the TFileXml class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLFILE_H__58C81085_95B4_4F0A_9E95_6F2AFD75ADA0__INCLUDED_)
#define AFX_XMLFILE_H__58C81085_95B4_4F0A_9E95_6F2AFD75ADA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PORTABLE

#include "level_0.h"
;
class TFileXml  
{
	FILE * fout;
public:
	void initWithFile(FILE * file) { fout = file; }
	void write(VCTIME vc);
	void write(TString &s);
	void write(const char * s);
	void write(DAYTIME dt);
	void write(int n);
	void write(double d);
	void write(TCHAR * p);
	TFileXml();
	virtual ~TFileXml();

};

#endif // !defined(AFX_XMLFILE_H__58C81085_95B4_4F0A_9E95_6F2AFD75ADA0__INCLUDED_)
