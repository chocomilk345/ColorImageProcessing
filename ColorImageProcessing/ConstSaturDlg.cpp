// ConstSaturDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing.h"
#include "afxdialogex.h"
#include "ConstSaturDlg.h"


// CConstSaturDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstSaturDlg, CDialog)

CConstSaturDlg::CConstSaturDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONST_SATUR, pParent)
	, m_constSatur(0)
	, m_const(0)
{

}

CConstSaturDlg::~CConstSaturDlg()
{
}

void CConstSaturDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_constSatur);
	DDV_MinMaxDouble(pDX, m_constSatur, 0, 1.0);
	DDX_Text(pDX, IDC_EDIT2, m_const);
	DDV_MinMaxDouble(pDX, m_const, -0.5, 0.5);
}


BEGIN_MESSAGE_MAP(CConstSaturDlg, CDialog)
END_MESSAGE_MAP()


// CConstSaturDlg 메시지 처리기
