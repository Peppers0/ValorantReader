
// ValorantCVDlg.h : header file
//

#pragma once

#include "ValorantReader.h"


// CValorantCVDlg dialog
class CValorantCVDlg : public CDialogEx
{
// Construction
public:
	CValorantCVDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VALORANTCV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CValorantReader m_valorantReader;
};
