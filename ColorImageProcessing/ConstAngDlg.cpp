// ConstAngDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing.h"
#include "afxdialogex.h"
#include "ConstAngDlg.h"


// CConstAngDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstAngDlg, CDialog)

CConstAngDlg::CConstAngDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONST_ANGLE, pParent)
	, m_angle(0)
{

}

CConstAngDlg::~CConstAngDlg()
{
}

void CConstAngDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_angle);
	DDV_MinMaxDouble(pDX, m_angle, 0, 90);
}


BEGIN_MESSAGE_MAP(CConstAngDlg, CDialog)
END_MESSAGE_MAP()


// CConstAngDlg 메시지 처리기
