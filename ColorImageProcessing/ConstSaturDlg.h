#pragma once
#include "afxdialogex.h"


// CConstSaturDlg 대화 상자

class CConstSaturDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstSaturDlg)

public:
	CConstSaturDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstSaturDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONST_SATUR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_constSatur;
	double m_const;
};
