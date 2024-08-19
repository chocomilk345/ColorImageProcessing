#pragma once
#include "afxdialogex.h"


// CConstAngDlg 대화 상자

class CConstAngDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstAngDlg)

public:
	CConstAngDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstAngDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONST_ANGLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_angle;
};
