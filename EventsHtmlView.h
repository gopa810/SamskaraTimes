// EventsHtmlView.h: interface for the CResultHtmlView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTSHTMLVIEW_H__826E67E3_AFF2_41FE_8628_9402671C8951__INCLUDED_)
#define AFX_EVENTSHTMLVIEW_H__826E67E3_AFF2_41FE_8628_9402671C8951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyWebView.h"

class CResultHtmlView : public CMyWebView  
{
public:
	virtual void OnBeforeNavigate2( LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel );
	CResultHtmlView();
	virtual ~CResultHtmlView();

};

#endif // !defined(AFX_EVENTSHTMLVIEW_H__826E67E3_AFF2_41FE_8628_9402671C8951__INCLUDED_)
