// TStringStorage.h: interface for the TStringStorage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSTRINGSTORAGE_H__4C5FCE98_DF8C_4FB8_924E_E26403499702__INCLUDED_)
#define AFX_TSTRINGSTORAGE_H__4C5FCE98_DF8C_4FB8_924E_E26403499702__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TStringStorage  
{
public:
	class TStringStoragePage
	{
	public:
		TStringStoragePage * next;
		char sz[1024];
		int top;
		TStringStoragePage()
		{
			next = NULL;
			top = 0;
		}
	};
	TStringStoragePage pages;
	const char * add(const char *pString);
	TStringStorage();
	virtual ~TStringStorage();

};

#endif // !defined(AFX_TSTRINGSTORAGE_H__4C5FCE98_DF8C_4FB8_924E_E26403499702__INCLUDED_)
