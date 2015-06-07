#pragma once

#include "vcal5beta.h"

// DlgSelectSamskara dialog

class DlgSelectSamskara : public CDialog
{
	DECLARE_DYNAMIC(DlgSelectSamskara)

public:
	DlgSelectSamskara(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgSelectSamskara();

// Dialog Data
	enum { IDD = IDD_DLGSELECTSAMSKARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_nNextStep;
	CListBox m_list;
	virtual BOOL OnInitDialog();
};
