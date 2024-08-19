
// ColorImageProcessingDoc.cpp: CColorImageProcessingDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageProcessing.h"
#endif

#include "ColorImageProcessingDoc.h"

#include <propkey.h>
#include <algorithm>
#include "ConstantDlg.h"
#include "Constant2Dlg.h"
#include "ConstAngDlg.h"
#include "ConstSaturDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorImageProcessingDoc

IMPLEMENT_DYNCREATE(CColorImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CColorImageProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CColorImageProcessingDoc 생성/소멸

CColorImageProcessingDoc::CColorImageProcessingDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CColorImageProcessingDoc::~CColorImageProcessingDoc()
{
}

BOOL CColorImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CColorImageProcessingDoc serialization

void CColorImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CColorImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CColorImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CColorImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CColorImageProcessingDoc 진단

#ifdef _DEBUG
void CColorImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CColorImageProcessingDoc 명령


unsigned char** CColorImageProcessingDoc::OnMalloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;
	memory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		memory[i] = new unsigned char[w];
	return memory;
}

double** CColorImageProcessingDoc::OnMalloc2D_double(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** memory;
	memory = new double* [h];
	for (int i = 0; i < h; i++)
		memory[i] = new double[w];
	return memory;
}

double** CColorImageProcessingDoc::OnMalloc2D(int h, int w, double initVal)
{
	// TODO: 여기에 구현 코드 추가.
	double** retMemory;

	retMemory = new double* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new double[w];

	return retMemory;
}

template <typename T>
void CColorImageProcessingDoc::OnFree2d(T** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}
/*
void CColorImageProcessingDoc::OnFree2d(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}

void CColorImageProcessingDoc::OnFree2d(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}*/

void CColorImageProcessingDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	OnFree2d(m_inImageR, m_inH);
	OnFree2d(m_inImageG, m_inH);
	OnFree2d(m_inImageB, m_inH);

	OnFree2d(m_outImageR, m_outH);
	OnFree2d(m_outImageG, m_outH);
	OnFree2d(m_outImageB, m_outH);

	CDocument::OnCloseDocument();
}


BOOL CColorImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 기존 메모리 해제
	if (m_inImageR != NULL) {
		OnFree2d(m_inImageR, m_inH);
		OnFree2d(m_inImageG, m_inH);
		OnFree2d(m_inImageB, m_inH);
		m_inImageR = m_inImageG = m_inImageB = NULL;
		m_inH = m_inW = 0;

		OnFree2d(m_outImageR, m_outH);
		OnFree2d(m_outImageG, m_outH);
		OnFree2d(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}

	CImage image;
	image.Load(lpszPathName);
	// (중요!) 입력 영상 크기 알아내기~
	m_inH = image.GetHeight();
	m_inW = image.GetWidth();
	// 메모리 할당
	m_inImageR = OnMalloc2D(m_inH, m_inW);
	m_inImageG = OnMalloc2D(m_inH, m_inW);
	m_inImageB = OnMalloc2D(m_inH, m_inW);
	// CImage의 객체값 --> 메모리
	COLORREF px;
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			px = image.GetPixel(k, i);
			m_inImageR[i][k] = GetRValue(px);
			m_inImageG[i][k] = GetGValue(px);
			m_inImageB[i][k] = GetBValue(px);
		}
	return TRUE;
}


BOOL CColorImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_outImageR == NULL)
		return FALSE;

	CImage image;
	image.Create(m_outW, m_outH, 32);

	unsigned char R, G, B;
	COLORREF px;

	for (int i = 0; i < m_outW; i++)
		for (int k = 0; k < m_outH; k++) {
			R = m_outImageR[k][i];
			G = m_outImageG[k][i];
			B = m_outImageB[k][i];
			px = RGB(R, G, B);
			image.SetPixel(i, k, px);
		}
	image.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"저장", L"성공", NULL);

	return TRUE;
}

void CColorImageProcessingDoc::OnFreeOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	if (m_outImageR != NULL) {
		OnFree2d(m_outImageR, m_outH);
		OnFree2d(m_outImageG, m_outH);
		OnFree2d(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}
}

void CColorImageProcessingDoc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[i][k];
			m_outImageG[i][k] = m_inImageG[i][k];
			m_outImageB[i][k] = m_inImageB[i][k];
		}
	}
}


void CColorImageProcessingDoc::OnGrayScale()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
		}
	}
}


void CColorImageProcessingDoc::OnAdd()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int value = (int)dlg.m_constant;
	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {

			if (m_inImageR[i][k] + value > 255)
				m_outImageR[i][k] = 255;
			else if (m_inImageR[i][k] + value < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = m_inImageR[i][k] + value;

			if (m_inImageG[i][k] + value > 255)
				m_outImageG[i][k] = 255;
			else if (m_inImageG[i][k] + value < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = m_inImageG[i][k] + value;

			if (m_inImageB[i][k] + value > 255)
				m_outImageB[i][k] = 255;
			else if (m_inImageB[i][k] + value < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = m_inImageB[i][k] + value;

		}
	}

}


void CColorImageProcessingDoc::OnMul()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int value = (int)dlg.m_constant;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {

			if (m_inImageR[i][k] * value > 255)
				m_outImageR[i][k] = 255;
			else if (m_inImageR[i][k] * value < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = (unsigned char)(m_inImageR[i][k] * value);

			if (m_inImageG[i][k] * value > 255)
				m_outImageG[i][k] = 255;
			else if (m_inImageG[i][k] * value < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = (unsigned char)(m_inImageG[i][k] * value);

			if (m_inImageB[i][k] * value > 255)
				m_outImageB[i][k] = 255;
			else if (m_inImageB[i][k] * value < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = (unsigned char)(m_inImageB[i][k] * value);

		}
	}
}


void CColorImageProcessingDoc::OnDiv()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int value = (int)dlg.m_constant;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {

			if (m_inImageR[i][k] / value > 255)
				m_outImageR[i][k] = 255;
			else if (m_inImageR[i][k] / value < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = (unsigned char)(m_inImageR[i][k] / value);

			if (m_inImageG[i][k] / value > 255)
				m_outImageG[i][k] = 255;
			else if (m_inImageG[i][k] / value < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = (unsigned char)(m_inImageG[i][k] / value);

			if (m_inImageB[i][k] / value > 255)
				m_outImageB[i][k] = 255;
			else if (m_inImageB[i][k] / value < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = (unsigned char)(m_inImageB[i][k] / value);

		}
	}
}


void CColorImageProcessingDoc::OnAnd()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int value = (int)dlg.m_constant;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {

			if ((m_inImageR[i][k] & value) > 255)
				m_outImageR[i][k] = 255;
			else if ((m_inImageR[i][k] & value) < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = m_inImageR[i][k] & value;

			if ((m_inImageG[i][k] & value) > 255)
				m_outImageG[i][k] = 255;
			else if ((m_inImageG[i][k] & value) < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = m_inImageG[i][k] & value;

			if ((m_inImageB[i][k] & value) > 255)
				m_outImageB[i][k] = 255;
			else if ((m_inImageB[i][k] & value) < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = m_inImageB[i][k] & value;

		}
	}
}


void CColorImageProcessingDoc::OnOr()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int value = (int)dlg.m_constant;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {

			if ((m_inImageR[i][k] | value) > 255)
				m_outImageR[i][k] = 255;
			else if ((m_inImageR[i][k] | value) < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = m_inImageR[i][k] | value;

			if ((m_inImageG[i][k] | value) > 255)
				m_outImageG[i][k] = 255;
			else if ((m_inImageG[i][k] | value) < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = m_inImageG[i][k] | value;

			if ((m_inImageB[i][k] | value) > 255)
				m_outImageB[i][k] = 255;
			else if ((m_inImageB[i][k] | value) < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = m_inImageB[i][k] | value;

		}
	}
}


void CColorImageProcessingDoc::OnXor()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int value = (int)dlg.m_constant;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {

			if ((m_inImageR[i][k] ^ value) > 255)
				m_outImageR[i][k] = 255;
			else if ((m_inImageR[i][k] ^ value) < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = m_inImageR[i][k] ^ value;

			if ((m_inImageG[i][k] ^ value) > 255)
				m_outImageG[i][k] = 255;
			else if ((m_inImageG[i][k] ^ value) < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = m_inImageG[i][k] ^ value;

			if ((m_inImageB[i][k] ^ value) > 255)
				m_outImageB[i][k] = 255;
			else if ((m_inImageB[i][k] ^ value) < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = m_inImageB[i][k] ^ value;

		}
	}
}


void CColorImageProcessingDoc::OnRev()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = 255 - m_inImageR[i][k];
			m_outImageG[i][k] = 255 - m_inImageG[i][k];
			m_outImageB[i][k] = 255 - m_inImageB[i][k];
		}
	}
}


void CColorImageProcessingDoc::OnBw()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			if (avg < 128)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 0;
			else
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 255;

		}
	}
}


void CColorImageProcessingDoc::OnBwAvg()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	double sum = 0, avg = 0, avgColor;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			sum += m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k];
		}
	}
	avg = sum / (m_outW * m_outH * 3);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			avgColor = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			if (avgColor < avg)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 0;
			else
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 255;

		}
	}
}


void CColorImageProcessingDoc::OnBwMed()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	unsigned char** grayImage = OnMalloc2D(m_outH, m_outW);
	unsigned char* array = new unsigned char[m_outH * m_outW];
	// ** 진짜 영상처리 알고리즘 **
	double avg;
	int median = 0, number = 0;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			grayImage[i][k] = (unsigned char)avg;
			array[number] = (unsigned char)avg;
			number++;
		}
	}

	std::sort(array, array + number);
	median = array[m_inH * m_inW / 2];

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (grayImage[i][k] < median)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 0;
			else
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 255;

		}
	}

}


void CColorImageProcessingDoc::OnGamma()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double value = dlg.m_constant;
	double temp;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			temp = m_inImageR[i][k];
			m_outImageR[i][k] = (unsigned char)(255.0 * pow(temp / 255.0, value));
			temp = m_inImageG[i][k];
			m_outImageG[i][k] = (unsigned char)(255.0 * pow(temp / 255.0, value));
			temp = m_inImageB[i][k];
			m_outImageB[i][k] = (unsigned char)(255.0 * pow(temp / 255.0, value));
		}
	}
}


void CColorImageProcessingDoc::OnPara()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double temp, val;
	// 밝은 곳 입체형 (CAP)
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {

			temp = m_inImageR[i][k];
			val = 255.0 - 255.0 * pow((temp / 128.0 - 1.0), 2);
			if (val > 255.0) val = 255.0;
			else if (val < 0.0) val = 0.0;
			m_outImageR[i][k] = (unsigned char)val;

			temp = m_inImageG[i][k];
			val = 255.0 - 255.0 * pow((temp / 128.0 - 1.0), 2);
			if (val > 255.0) val = 255.0;
			else if (val < 0.0) val = 0.0;
			m_outImageG[i][k] = (unsigned char)val;

			temp = m_inImageB[i][k];
			val = 255.0 - 255.0 * pow((temp / 128.0 - 1.0), 2);
			if (val > 255.0) val = 255.0;
			else if (val < 0.0) val = 0.0;
			m_outImageB[i][k] = (unsigned char)val;
		}
	}

}


void CColorImageProcessingDoc::OnPara2()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double temp, val;
	// 밝은 곳 입체형 (CAP)
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {

			temp = m_inImageR[i][k];
			val = 255.0 * pow((temp / 128.0 - 1.0), 2);
			if (val > 255.0) val = 255.0;
			else if (val < 0.0) val = 0.0;
			m_outImageR[i][k] = (unsigned char)val;

			temp = m_inImageG[i][k];
			val = 255.0 * pow((temp / 128.0 - 1.0), 2);
			if (val > 255.0) val = 255.0;
			else if (val < 0.0) val = 0.0;
			m_outImageG[i][k] = (unsigned char)val;

			temp = m_inImageB[i][k];
			val = 255.0 * pow((temp / 128.0 - 1.0), 2);
			if (val > 255.0) val = 255.0;
			else if (val < 0.0) val = 0.0;
			m_outImageB[i][k] = (unsigned char)val;
		}
	}
}


void CColorImageProcessingDoc::OnPost()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int val = (int)dlg.m_constant;
	int interval = (int)(255 / val);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) { // 값이 제일 낮은 영역 0으로 할당
			if (m_inImageR[i][k] < interval)
				m_outImageR[i][k] = 0;
			else if (m_inImageR[i][k] > interval * (val - 1)) // 값이 제일 큰 영역 255로 할당
				m_outImageR[i][k] = 255;

			if (m_inImageG[i][k] < interval)
				m_outImageG[i][k] = 0;
			else if (m_inImageG[i][k] > interval * (val - 1)) // 값이 제일 큰 영역 255로 할당
				m_outImageG[i][k] = 255;

			if (m_inImageB[i][k] < interval)
				m_outImageB[i][k] = 0;
			else if (m_inImageB[i][k] > interval * (val - 1)) // 값이 제일 큰 영역 255로 할당
				m_outImageB[i][k] = 255;
		}
	}

	for (int i = 1; i < val - 1; i++) { // 영역 입력값에 비례하여 할당
		for (int j = 0; j < m_inH; j++) {
			for (int k = 0; k < m_inW; k++) {
				if (m_inImageR[j][k] > interval * i && m_inImageR[j][k] < interval * (i + 1))
					m_outImageR[j][k] = interval * (i + 1);
				if (m_inImageG[j][k] > interval * i && m_inImageG[j][k] < interval * (i + 1))
					m_outImageG[j][k] = interval * (i + 1);
				if (m_inImageB[j][k] > interval * i && m_inImageB[j][k] < interval * (i + 1))
					m_outImageB[j][k] = interval * (i + 1);
			}
		}
	}
}


void CColorImageProcessingDoc::OnStress()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant2Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int start = (int)dlg.m_constant;
	int end = (int)dlg.m_constant2;

	if (start > end) {
		int temp = start;
		start = end;
		end = temp;
	}
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if ((m_inImageR[i][k] >= start && m_inImageR[i][k] <= end) && (m_inImageG[i][k] >= start && m_inImageG[i][k] <= end) && (m_inImageB[i][k] >= start && m_inImageB[i][k] <= end)) {
				m_outImageR[i][k] = 255;
				m_outImageG[i][k] = 255;
				m_outImageB[i][k] = 255;
			}
			else {
				m_outImageR[i][k] = m_inImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k];
			}
			//if (m_inImageR[i][k] >= start && m_inImageR[i][k] <= end)
			//	m_outImageR[i][k] = 255;
			//else
			//	m_outImageR[i][k] = m_inImageR[i][k];

			//if (m_inImageG[i][k] >= start && m_inImageG[i][k] <= end)
			//	m_outImageG[i][k] = 255;
			//else
			//	m_outImageG[i][k] = m_inImageG[i][k];

			//if (m_inImageB[i][k] >= start && m_inImageB[i][k] <= end)
			//	m_outImageB[i][k] = 255;
			//else
			//	m_outImageB[i][k] = m_inImageB[i][k];
		}
	}

}

/*
void CColorImageProcessingDoc::OnChangeSatur()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0]; S = hsi[1]; I = hsi[2];

			/// 채도(S) 흐리게 
			S = S - 0.2;
			if (S < 0)
				S = 0.0;
			// HSI --> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0]; G = rgb[1]; B = rgb[2];

			m_outImageR[i][k] = R;
			m_outImageG[i][k] = G;
			m_outImageB[i][k] = B;
		}
	}
}
*/
void CColorImageProcessingDoc::OnSaturAdd()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0]; S = hsi[1]; I = hsi[2];

			/// 채도(S) 선명하게 
			S = S + 0.2;
			if (S > 1)
				S = 1.0;
			// HSI --> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0]; G = rgb[1]; B = rgb[2];

			m_outImageR[i][k] = R;
			m_outImageG[i][k] = G;
			m_outImageB[i][k] = B;
		}
	}
}


void CColorImageProcessingDoc::OnSaturSub()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0]; S = hsi[1]; I = hsi[2];

			/// 채도(S) 흐리게 
			S = S - 0.2;
			if (S < 0)
				S = 0.0;
			// HSI --> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0]; G = rgb[1]; B = rgb[2];

			m_outImageR[i][k] = R;
			m_outImageG[i][k] = G;
			m_outImageB[i][k] = B;
		}
	}
}

void CColorImageProcessingDoc::OnChangeSatur()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	double value = dlg.m_constant;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0]; S = hsi[1]; I = hsi[2];

			/// 채도(S) 변경 
			S = S + value;
			if (S < 0)
				S = 0.0;
			else if (S > 1.0)
				S = 1.0;
			// HSI --> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0]; G = rgb[1]; B = rgb[2];

			m_outImageR[i][k] = R;
			m_outImageG[i][k] = G;
			m_outImageB[i][k] = B;
		}
	}
}
void CColorImageProcessingDoc::OnChangeInten()
{
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	double value = dlg.m_constant;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0]; S = hsi[1];  I = hsi[2];

			/// 명도 (S) 변경
			I = I + value;
			if (I < 0)
				I = 0.0;
			else if (I > 255.0)
				I = 255.0;
			// HSI --> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0]; G = rgb[1]; B = rgb[2];

			m_outImageR[i][k] = R;
			m_outImageG[i][k] = G;
			m_outImageB[i][k] = B;
		}
	}
}

void CColorImageProcessingDoc::OnChangeColor()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	double value = dlg.m_constant;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0]; S = hsi[1];  I = hsi[2];

			/// 색상 (H) 변경
			H = H + value;
			if (H < 0)
				H = 0.0;
			else if (H > 360.0)
				H = 360.0;
			// HSI --> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0]; G = rgb[1]; B = rgb[2];

			m_outImageR[i][k] = R;
			m_outImageG[i][k] = G;
			m_outImageB[i][k] = B;
		}
	}
}

double* CColorImageProcessingDoc::RGB2HSI(int R, int G, int B)
{
	// TODO: 여기에 구현 코드 추가.
	double H, S, I;
	double* HSI = new double[3];
	double min_value, angle;
	I = (R + G + B) / 3.0; // 밝기
	if ((R == G) && (G == B)) { // 그레이
		S = 0.0;
		H = 0.0;
	}
	else {

		min_value = min(min(R, G), B); //최소값 추출
		angle = (R - 0.5 * G - 0.5 * B) / (double)sqrt((R - G) * (R - G) + (R - B) * (G - B));

		H = (double)acos(angle) * 57.29577951;
		S = 1.0f - (3.0 / (R + G + B)) * min_value;
	}
	if (B > G) H = 360. - H;

	HSI[0] = H;
	HSI[1] = S;
	HSI[2] = I;

	return HSI;
}


unsigned char* CColorImageProcessingDoc::HSI2RGB(double H, double S, double I)
{
	// TODO: 여기에 구현 코드 추가.
	double R, G, B;
	unsigned char* RGB = new unsigned char[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;
	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}
	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = (unsigned char)R;
	RGB[1] = (unsigned char)G;
	RGB[2] = (unsigned char)B;
	return RGB;
}


void CColorImageProcessingDoc::OnPickOrange()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0]; S = hsi[1]; I = hsi[2];

			/// 오렌지 추출 (H: 8~20)
//			if (8 <= H && H <= 20) {
			if (54 <= H && H <= 66) {
				m_outImageR[i][k] = m_inImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k];
			}
			else {
				double avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (m_inImageB[i][k]) = (unsigned char)avg;
			}

		}
	}

}




void CColorImageProcessingDoc::OnMov()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant2Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int moveX = (int)dlg.m_constant;
	int moveY = (int)dlg.m_constant2;

	int x = 0, y = 0;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			x = k - moveX;
			y = i - moveY;
			if (x >= 0 && x < m_inW && y >= 0 && y < m_inH) {
				m_outImageR[i][k] = m_inImageR[y][x];
				m_outImageG[i][k] = m_inImageG[y][x];
				m_outImageB[i][k] = m_inImageB[y][x];
			}
			else {
				m_outImageR[i][k] = 0; // 배경색 검정
				m_outImageG[i][k] = 0;
				m_outImageB[i][k] = 0;
			}

		}
	}
}


void CColorImageProcessingDoc::OnMirHor()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[i][m_outW - 1 - k];
			m_outImageG[i][k] = m_inImageG[i][m_outW - 1 - k];
			m_outImageB[i][k] = m_inImageB[i][m_outW - 1 - k];
		}
	}
}


void CColorImageProcessingDoc::OnMirVer()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[m_inH - 1 - i][k];
			m_outImageG[i][k] = m_inImageG[m_inH - 1 - i][k];
			m_outImageB[i][k] = m_inImageB[m_inH - 1 - i][k];
		}
	}
}


void CColorImageProcessingDoc::OnZoomin()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	int scale = (int)dlg.m_constant;
	m_outH = (int)(m_inH * scale);
	m_outW = (int)(m_inW * scale);
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[(int)(i * scale)][(int)(k * scale)] = m_inImageR[i][k];
			m_outImageR[(int)(i * scale + 1)][(int)(k * scale + 1)] = m_inImageR[i][k];
			m_outImageG[(int)(i * scale)][(int)(k * scale)] = m_inImageG[i][k];
			m_outImageG[(int)(i * scale + 1)][(int)(k * scale + 1)] = m_inImageG[i][k];
			m_outImageB[(int)(i * scale)][(int)(k * scale)] = m_inImageB[i][k];
			m_outImageB[(int)(i * scale + 1)][(int)(k * scale + 1)] = m_inImageB[i][k];
		}
	}
}


void CColorImageProcessingDoc::OnZoomin2()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	int scale = (int)dlg.m_constant;
	m_outH = (int)(m_inH * scale);
	m_outW = (int)(m_inW * scale);
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = m_inImageR[(int)(i / scale)][(int)k / scale];
			m_outImageG[i][k] = m_inImageG[(int)(i / scale)][(int)k / scale];
			m_outImageB[i][k] = m_inImageB[(int)(i / scale)][(int)k / scale];
		}
	}
}


void CColorImageProcessingDoc::OnZoomin3()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	int i_H, i_W;
	unsigned char newValue;
	double ZoomRate, r_H, r_W, s_H, s_W;
	double C1, C2, C3, C4;
	double** tempImageR = NULL;
	double** tempImageG = NULL;
	double** tempImageB = NULL;

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	ZoomRate = dlg.m_constant;
	m_outH = (int)(m_inH * ZoomRate);
	m_outW = (int)(m_inW * ZoomRate);
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	tempImageR = OnMalloc2D(m_inH, m_inW, 0.0);
	tempImageG = OnMalloc2D(m_inH, m_inW, 0.0);
	tempImageB = OnMalloc2D(m_inH, m_inW, 0.0);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tempImageR[i][k] = (double)m_inImageR[i][k];
			tempImageG[i][k] = (double)m_inImageG[i][k];
			tempImageB[i][k] = (double)m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			r_H = i / ZoomRate;
			r_W = k / ZoomRate;

			i_H = (int)floor(r_H);
			i_W = (int)floor(r_W);

			s_H = r_H - i_H;
			s_W = r_W - i_W;

			if (i_H < 0 || i_H >= (m_inH - 1) || i_W < 0 || i_W >= (m_inW - 1)) {
				m_outImageR[i][k] = 255;
				m_outImageG[i][k] = 255;
				m_outImageB[i][k] = 255;
			}
			else { // 소수점 값 보간하기
				C1 = (double)tempImageR[i_H][i_W];
				C2 = (double)tempImageR[i_H][i_W + 1];
				C3 = (double)tempImageR[i_H + 1][i_W + 1];
				C4 = (double)tempImageR[i_H + 1][i_W];

				newValue = (unsigned char)(C1 * (1 - s_H) * (1 - s_W) + C2 * s_W * (1 - s_H) + C3 * s_W * s_H + C4 * (1 - s_W) * s_H);
				m_outImageR[i][k] = newValue;

				C1 = (double)tempImageG[i_H][i_W];
				C2 = (double)tempImageG[i_H][i_W + 1];
				C3 = (double)tempImageG[i_H + 1][i_W + 1];
				C4 = (double)tempImageG[i_H + 1][i_W];

				newValue = (unsigned char)(C1 * (1 - s_H) * (1 - s_W) + C2 * s_W * (1 - s_H) + C3 * s_W * s_H + C4 * (1 - s_W) * s_H);
				m_outImageG[i][k] = newValue;

				C1 = (double)tempImageB[i_H][i_W];
				C2 = (double)tempImageB[i_H][i_W + 1];
				C3 = (double)tempImageB[i_H + 1][i_W + 1];
				C4 = (double)tempImageB[i_H + 1][i_W];

				newValue = (unsigned char)(C1 * (1 - s_H) * (1 - s_W) + C2 * s_W * (1 - s_H) + C3 * s_W * s_H + C4 * (1 - s_W) * s_H);
				m_outImageB[i][k] = newValue;
			}

		}
	}
	OnFree2d(tempImageR, m_inH);
	OnFree2d(tempImageG, m_inH);
	OnFree2d(tempImageB, m_inH);
}

void CColorImageProcessingDoc::OnZoomout()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	int scale = (int)dlg.m_constant;
	m_outH = (int)(m_inH / scale) + 1;
	m_outW = (int)(m_inW / scale) + 1;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[(int)(i / scale)][(int)(k / scale)] = m_inImageR[i][k];
			m_outImageG[(int)(i / scale)][(int)(k / scale)] = m_inImageG[i][k];
			m_outImageB[(int)(i / scale)][(int)(k / scale)] = m_inImageB[i][k];
		}
	}
}

void CColorImageProcessingDoc::OnZoomoutAvg()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	int scale = (int)dlg.m_constant;
	m_outH = (int)(m_inH / scale);
	m_outW = (int)(m_inW / scale);
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int sumR, sumG, sumB, avgR, avgG, avgB;
	for (int i = 0; i < m_inH; i += scale) {
		for (int k = 0; k < m_inW; k += scale) {
			sumR = 0, sumG = 0, sumB = 0, avgR = 0, avgG = 0, avgB = 0;

			for (int x = 0; x < scale; x++) {
				for (int y = 0; y < scale; y++) {
					sumR += m_inImageR[i + x][k + y];
					sumG += m_inImageG[i + x][k + y];
					sumB += m_inImageB[i + x][k + y];
				}
			}
			avgR = (int)(sumR / (scale * scale));
			avgG = (int)(sumG / (scale * scale));
			avgB = (int)(sumB / (scale * scale));

			m_outImageR[(int)(i / scale)][(int)(k / scale)] = avgR;
			m_outImageG[(int)(i / scale)][(int)(k / scale)] = avgG;
			m_outImageB[(int)(i / scale)][(int)(k / scale)] = avgB;
		}
	}
}


void CColorImageProcessingDoc::OnZoomoutMed()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	int scale = (int)dlg.m_constant;
	m_outH = (int)(m_inH / scale);
	m_outW = (int)(m_inW / scale);
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	int medR = 0, medG = 0, medB = 0, number = 0;
	unsigned char* arrayR = new unsigned char[scale * scale];
	unsigned char* arrayG = new unsigned char[scale * scale];
	unsigned char* arrayB = new unsigned char[scale * scale];

	for (int i = 0; i < m_inH; i += scale) {
		for (int k = 0; k < m_inW; k += scale) {
			
			number = 0;

			for (int x = 0; x < scale; x++) {
				for (int y = 0; y < scale; y++) {
					arrayR[number] = m_inImageR[i + x][k + y];
					arrayG[number] = m_inImageG[i + x][k + y];
					arrayB[number] = m_inImageB[i + x][k + y];
					number++;
				}
			}

			std::sort(arrayR, arrayR + number);
			medR = arrayR[(int)(scale * scale / 2)];

			std::sort(arrayG, arrayG + number);
			medG = arrayG[(int)(scale * scale / 2)];

			std::sort(arrayB, arrayB + number);
			medB = arrayB[(int)(scale * scale / 2)];

			m_outImageR[(int)(i / scale)][(int)(k / scale)] = medR;
			m_outImageG[(int)(i / scale)][(int)(k / scale)] = medG;
			m_outImageB[(int)(i / scale)][(int)(k / scale)] = medB;
		}

	}

	delete[] arrayR;
	delete[] arrayG;
	delete[] arrayB;
}



void CColorImageProcessingDoc::OnRotate()
{
	// TODO: 여기에 구현 코드 추가.
	CConstAngDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int degree = (int)dlg.m_angle;
	double radian = degree * 3.141592 / 180.0;
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int xs = i;
			int ys = k;
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);

			if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW)) {
				m_outImageR[xd][yd] = m_inImageR[xs][ys];
				m_outImageG[xd][yd] = m_inImageG[xs][ys];
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
			}
		}
	}
}


void CColorImageProcessingDoc::OnRotate2()
{
	// TODO: 여기에 구현 코드 추가.
	CConstAngDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int degree = (int)dlg.m_angle;
	double radian = degree * 3.141592 / 180.0;
	int cx = m_inH / 2;
	int cy = m_inW / 2;

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int xd = i;
			int yd = k;

			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW)) {
				m_outImageR[xd][yd] = m_inImageR[xs][ys];
				m_outImageG[xd][yd] = m_inImageG[xs][ys];
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
			}
			else {
				m_outImageR[xd][yd] = 0;
				m_outImageG[xd][yd] = 0;
				m_outImageB[xd][yd] = 0;
			}

		}
	}
}


void CColorImageProcessingDoc::OnRotate3()
{
	// TODO: 여기에 구현 코드 추가.
	CConstAngDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	OnFreeOutImage();

	int degree = (int)dlg.m_angle;
	double radian = (double)(degree * 3.141592 / 180.0);
	double radian2 = (double)((90 - degree) * 3.141592 / 180.0);

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outW = (int)(m_inH * cos(radian2) + m_inW * cos(radian));
	m_outH = (int)(m_inH * cos(radian) + m_inW * cos(radian2));
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int cx = m_inH / 2;
	int cy = m_inW / 2;
	int centerX = m_outH / 2;
	int centerY = m_outW / 2;

	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int xd = i;
			int yd = k;

			int xs = (int)(cos(radian) * (xd - centerX) + sin(radian) * (yd - centerY));
			int ys = (int)(-sin(radian) * (xd - centerX) + cos(radian) * (yd - centerY));
			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < m_inH) && (0 <= ys && ys < m_inW)) {
				m_outImageR[xd][yd] = m_inImageR[xs][ys];
				m_outImageG[xd][yd] = m_inImageG[xs][ys];
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
			}
			else {
				m_outImageR[xd][yd] = 0;
				m_outImageG[xd][yd] = 0;
				m_outImageB[xd][yd] = 0;
			}
		}
	}
}

void CColorImageProcessingDoc::OnHistroStretch()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	// new = (old - low) / (high - low) * 255.0
	double high = (m_inImageR[0][0] + m_inImageG[0][0] + m_inImageB[0][0]) / 3.;
	double low = (m_inImageR[0][0] + m_inImageG[0][0] + m_inImageB[0][0]) / 3.;
	double temp;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			temp = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			if (temp > high)
				high = temp;
			if (temp < low)
				low = temp;
		}
	}
	int old, newVal;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = m_inImageR[i][k];
			newVal = (int)((old - low) / (high - low) * 255.0);
			if (newVal > 255)
				newVal = 255;
			else if (newVal < 0)
				newVal = 0;
			m_outImageR[i][k] = newVal;

			old = m_inImageG[i][k];
			newVal = (int)((old - low) / (high - low) * 255.0);
			if (newVal > 255)
				newVal = 255;
			else if (newVal < 0)
				newVal = 0;
			m_outImageG[i][k] = newVal;

			old = m_inImageB[i][k];
			newVal = (int)((old - low) / (high - low) * 255.0);
			if (newVal > 255)
				newVal = 255;
			else if (newVal < 0)
				newVal = 0;
			m_outImageB[i][k] = newVal;
		}
	}

}

void CColorImageProcessingDoc::OnEndin() {
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	// new = (old - low) / (high - low) * 255.0
	double high = (m_inImageR[0][0] + m_inImageG[0][0] + m_inImageB[0][0]) / 3.;
	double low = (m_inImageR[0][0] + m_inImageG[0][0] + m_inImageB[0][0]) / 3.;
	double temp;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			temp = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			if (temp > high)
				high = temp;
			if (temp < low)
				low = temp;
		}
	}
	high -= 50;
	low += 50;
	int old, newVal;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = m_inImageR[i][k];
			newVal = (int)((old - low) / (high - low) * 255.0);
			if (newVal > 255)
				newVal = 255;
			else if (newVal < 0)
				newVal = 0;
			m_outImageR[i][k] = newVal;

			old = m_inImageG[i][k];
			newVal = (int)((old - low) / (high - low) * 255.0);
			if (newVal > 255)
				newVal = 255;
			else if (newVal < 0)
				newVal = 0;
			m_outImageG[i][k] = newVal;

			old = m_inImageB[i][k];
			newVal = (int)((old - low) / (high - low) * 255.0);
			if (newVal > 255)
				newVal = 255;
			else if (newVal < 0)
				newVal = 0;
			m_outImageB[i][k] = newVal;
		}
	}

}

void CColorImageProcessingDoc::OnHistoEqual()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 1단계 : 빈도수 세기(=히스토그램) histo[256]
	int histoR[256] = { 0, }, histoG[256] = { 0, }, histoB[256] = { 0, };
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			histoR[m_inImageR[i][k]]++;
			histoG[m_inImageG[i][k]]++;
			histoB[m_inImageB[i][k]]++;
		}
	// 2단계 : 누적히스토그램 생성
	int sumHistoR[256] = { 0, }, sumHistoG[256] = { 0, }, sumHistoB[256] = { 0, };
	sumHistoR[0] = histoR[0];
	sumHistoG[0] = histoG[0];
	sumHistoB[0] = histoB[0];
	for (int i = 1; i < 256; i++) {
		sumHistoR[i] = sumHistoR[i - 1] + histoR[i];
		sumHistoG[i] = sumHistoG[i - 1] + histoG[i];
		sumHistoB[i] = sumHistoB[i - 1] + histoB[i];
	}
	// 3단계 : 정규화된 히스토그램 생성  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
	double normalHistoR[256] = { 1.0, }, normalHistoG[256] = { 1.0, }, normalHistoB[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHistoR[i] = sumHistoR[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoG[i] = sumHistoG[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoB[i] = sumHistoB[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}
	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = (unsigned char)normalHistoR[m_inImageR[i][k]];
			m_outImageG[i][k] = (unsigned char)normalHistoG[m_inImageG[i][k]];
			m_outImageB[i][k] = (unsigned char)normalHistoB[m_inImageB[i][k]];
		}
	}
}

/*
void CColorImageProcessingDoc::OnHistoEqual() // HSI
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageB = OnMalloc2D_double(m_inH, m_inW);

	tmpInImageH = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageS = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageI = OnMalloc2D_double(m_inH, m_inW);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i][k] = m_inImageR[i][k];
			tmpInImageG[i][k] = m_inImageG[i][k];
			tmpInImageB[i][k] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k];
			G = (unsigned char)tmpInImageG[i][k];
			B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	// 1단계 : 빈도수 세기 (=히스토그램)
	int histo[256] = { 0, };
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) 
			histo[(int)tmpInImageI[i][k]]++;

	// 2단계 : 누적히스토그램 생성
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 0; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];

	// 3단계 : 정규화된 히스토그램 생성 normalHisto = sumHisto * (1.0/(inH*inW)) * 255.0
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 101; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}

	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
//			tmpInImageI[i][k] = normalHisto[(int)(normalHisto[i][k] * 100)]/100.0;
			tmpInImageI[i][k] = normalHisto[(int)tmpInImageI[i][k]];
		}
	}
	// new = (old - low) / (high - low) * 255.0

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH);
	OnFree2d(tmpInImageG, m_inH);
	OnFree2d(tmpInImageB, m_inH);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH);
	OnFree2d(tmpInImageS, m_inH);
	OnFree2d(tmpInImageI, m_inH);
}*/
/*
void CColorImageProcessingDoc::OnHistroStretch()  // HSI
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageB = OnMalloc2D_double(m_inH, m_inW);

	tmpInImageH = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageS = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageI = OnMalloc2D_double(m_inH, m_inW);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i][k] = m_inImageR[i][k];
			tmpInImageG[i][k] = m_inImageG[i][k];
			tmpInImageB[i][k] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k];
			G = (unsigned char)tmpInImageG[i][k];
			B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// new = (old - low) / (high - low) * 255.0
	double high = tmpInImageI[0][0], low = tmpInImageI[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (tmpInImageI[i][k] > high)
				high = tmpInImageI[i][k];
			if (tmpInImageI[i][k] < low)
				low = tmpInImageI[i][k];
		}
	}

	double old, newVal;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = tmpInImageI[i][k];
			newVal = (int)((old - low) / (high - low) * 255.0);
			if (newVal > 255)
				newVal = 255;
			else if (newVal < 0)
				newVal = 0;
			tmpInImageI[i][k] = newVal;
		}
	}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH);
	OnFree2d(tmpInImageG, m_inH);
	OnFree2d(tmpInImageB, m_inH);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH);
	OnFree2d(tmpInImageS, m_inH);
	OnFree2d(tmpInImageI, m_inH);
}
*/
/*
void CColorImageProcessingDoc::OnEndin() // HSI
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageB = OnMalloc2D_double(m_inH, m_inW);

	tmpInImageH = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageS = OnMalloc2D_double(m_inH, m_inW);
	tmpInImageI = OnMalloc2D_double(m_inH, m_inW);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i][k] = m_inImageR[i][k];
			tmpInImageG[i][k] = m_inImageG[i][k];
			tmpInImageB[i][k] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k];
			G = (unsigned char)tmpInImageG[i][k];
			B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// new = (old - low) / (high - low) * 255.0
	double high = tmpInImageI[0][0], low = tmpInImageI[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (tmpInImageI[i][k] > high)
				high = tmpInImageI[i][k];
			if (tmpInImageI[i][k] < low)
				low = tmpInImageI[i][k];
		}
	}
	high -= 50;
	low += 50;

	double old, newVal;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = tmpInImageI[i][k];
			newVal = (int)((old - low) / (high - low) * 255.0);
			if (newVal > 255)
				newVal = 255;
			else if (newVal < 0)
				newVal = 0;
			tmpInImageI[i][k] = newVal;
		}
	}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH);
	OnFree2d(tmpInImageG, m_inH);
	OnFree2d(tmpInImageB, m_inH);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH);
	OnFree2d(tmpInImageS, m_inH);
	OnFree2d(tmpInImageI, m_inH);
}
*/


void CColorImageProcessingDoc::OnEmboss()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = { // 엠보싱 마스크
		{-1.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 1.0} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}
	}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
}

void CColorImageProcessingDoc::OnEmbossHsi()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = { // 엠보싱 마스크
		{-1.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 1.0} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k];
			G = (unsigned char)tmpInImageG[i][k]; 
			B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127;
		}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);
}


void CColorImageProcessingDoc::OnBlur()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = { // 블러링 마스크
		{1. / 9, 1. / 9, 1. / 9},
		{1. / 9, 1. / 9, 1. / 9},
		{1. / 9, 1. / 9, 1. / 9} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	//for (int i = 0; i < m_inH; i++)
	//	for (int k = 0; k < m_inW; k++) {
	//		tmpInImageI[i][k] += 127;
	//	}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);
}


void CColorImageProcessingDoc::OnBlur2()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 9;
	double mask[MSIZE][MSIZE] = { // 블러링 마스크
		{1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81 },
		{1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81 },
		{1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81 },
		{1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81 },
		{1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81 },
		{1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81 },
		{1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81 },
		{1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81 },
		{1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81,1. / 81, 1. / 81, 1. / 81 } };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageG = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageB = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);

	tmpInImageH = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageS = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageI = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + MSIZE-1; i++)
		for (int k = 0; k < m_inW + MSIZE - 1; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 4][k + 4] = m_inImageR[i][k];
			tmpInImageG[i + 4][k + 4] = m_inImageG[i][k];
			tmpInImageB[i + 4][k + 4] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	//for (int i = 0; i < m_inH; i++)
	//	for (int k = 0; k < m_inW; k++) {
	//		tmpInImageI[i][k] += 127;
	//	}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageG, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageB, m_inH + MSIZE - 1);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageS, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageI, m_inH + MSIZE - 1);
}


void CColorImageProcessingDoc::OnSharp()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = { // 샤프닝 마스크
		{-1., -1., -1.},
		{-1., 9., -1.},
		{-1., -1., -1.} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	//for (int i = 0; i < m_inH; i++)
	//	for (int k = 0; k < m_inW; k++) {
	//		tmpInImageI[i][k] += 127;
	//	}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);
}

void CColorImageProcessingDoc::OnSharpHpf()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = { // 샤프닝 마스크
		{-1. / 9., -1. / 9., -1. / 9.},
		{-1. / 9., 8. / 9., -1. / 9.},
		{-1. / 9., -1. / 9., -1. / 9.} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127;
		}


	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);
}

void CColorImageProcessingDoc::OnEdge1()
{
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	unsigned char** grayImage = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) { // GrayScale
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			grayImage[i][k] = (unsigned char)avg;
		}
	}

	////////////////////
	// 화소 영역 처리
	////////////////////
	double mask[3][3] = { {0.0, 0.0, 0.0}, // 수직 에지 검출 마스크
						  {-1.0, 1.0, 0.0},
						  {0.0,  0.0, 0.0} };

	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc2D_double(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값 
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = grayImage[i][k];

	// ** 회선 연산 ** 
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3)와 한점을 중심으로 한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 255;
			else
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree2d(tmpInImage, m_inH + 2);
	OnFree2d(tmpOutImage, m_inH);
	OnFree2d(grayImage, m_inH);
}

void CColorImageProcessingDoc::OnEdgeHomo()
{
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	unsigned char** grayImage = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) { // GrayScale
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			grayImage[i][k] = (unsigned char)avg;
		}
	}

	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc2D_double(m_outH, m_outW);
	double max;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImage[i + 1][k + 1] = (double)grayImage[i][k];
		}
	}

	int n, m;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			max = 0.0; // 블록이 이동할 때마다 최대값 초기화
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					if (fabs(tmpInImage[i + 1][k + 1] - tmpInImage[i + n][k + m]) >= max)
						max = fabs(tmpInImage[i + 1][k + 1] - tmpInImage[i + n][k + m]);
				}
			}
			tmpOutImage[i][k] = max;
		}
	}
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (tmpOutImage[i][k] > 255.)
				tmpOutImage[i][k] = 255.;
			else if (tmpOutImage[i][k] < 0.)
				tmpOutImage[i][k] = 0.;
		}
	}
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree2d(tmpInImage, m_inH + 2);
	OnFree2d(tmpOutImage, m_inH);
	OnFree2d(grayImage, m_inH);
}

void CColorImageProcessingDoc::OnEdgeSub()
{
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	unsigned char** grayImage = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) { // GrayScale
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			grayImage[i][k] = (unsigned char)avg;
		}
	}

	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc2D_double(m_outH, m_outW);
	double max, temp;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImage[i + 1][k + 1] = (double)grayImage[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			max = 0.0; // 블록이 이동할 때마다 최대값 초기화
			temp = fabs(tmpInImage[i][k] - tmpInImage[i + 2][k + 2]);
			if (temp >= max) max = temp;
			temp = fabs(tmpInImage[i][k + 1] - tmpInImage[i + 2][k + 1]);
			if (temp >= max) max = temp;
			temp = fabs(tmpInImage[i][k + 2] - tmpInImage[i + 2][k]);
			if (temp >= max) max = temp;
			temp = fabs(tmpInImage[i + 1][k] - tmpInImage[i + 1][k + 1]);
			if (temp >= max) max = temp;

			tmpOutImage[i][k] = max;
		}
	}
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (tmpOutImage[i][k] > 255.)
				tmpOutImage[i][k] = 255.;
			else if (tmpOutImage[i][k] < 0.)
				tmpOutImage[i][k] = 0.;
		}
	}
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree2d(tmpInImage, m_inH + 2);
	OnFree2d(tmpOutImage, m_inH);
	OnFree2d(grayImage, m_inH);
}

void CColorImageProcessingDoc::OnRobert()
{
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	unsigned char** grayImage = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) { // GrayScale
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			grayImage[i][k] = (unsigned char)avg;
		}
	}

	////////////////////
	// 화소 영역 처리
	////////////////////
	double mask[3][3] = { {-1.0, 0.0, 0.0},    // 로버츠 마스크 행 검출
						  {0.0,  1.0, 0.0},
						  {0.0,  0.0, 0.0} };

	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc2D_double(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값 
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = grayImage[i][k];

	// ** 회선 연산 ** 
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3)와 한점을 중심으로 한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 255;
			else
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree2d(tmpInImage, m_inH + 2);
	OnFree2d(tmpOutImage, m_inH);
	OnFree2d(grayImage, m_inH);
}

void CColorImageProcessingDoc::OnSobel() 
{
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	unsigned char** grayImage = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) { // GrayScale
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			grayImage[i][k] = (unsigned char)avg;
		}
	}

	////////////////////
	// 화소 영역 처리
	////////////////////
	double mask[3][3] = { {-1.0, -2.0, -1.0}, // 소벨 마스크 행 검출
						  {0.0,  0.0, 0.0},
						  {1.0,  2.0, 1.0} };

	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc2D_double(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값 
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = grayImage[i][k];

	// ** 회선 연산 ** 
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3)와 한점을 중심으로 한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 255;
			else
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree2d(tmpInImage, m_inH + 2);
	OnFree2d(tmpOutImage, m_inH);
	OnFree2d(grayImage, m_inH);
}

void CColorImageProcessingDoc::OnLapla() 
{
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	unsigned char** grayImage = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) { // GrayScale
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			grayImage[i][k] = (unsigned char)avg;
		}
	}

	////////////////////
	// 화소 영역 처리
	////////////////////
	double mask[3][3] = { {-1.0, -1.0, -1.0},    // 라플라시안 마스크
						  {-1.0,  8.0, -1.0},
						  {-1.0, -1.0, -1.0} };

	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc2D_double(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값 
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImage[i + 1][k + 1] = grayImage[i][k];
		}

	// ** 회선 연산 ** 
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3)와 한점을 중심으로 한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 255;
			else
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree2d(tmpInImage, m_inH + 2);
	OnFree2d(tmpOutImage, m_inH);
	OnFree2d(grayImage, m_inH);
}

void CColorImageProcessingDoc::OnLog()
{
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	unsigned char** grayImage = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) { // GrayScale
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			grayImage[i][k] = (unsigned char)avg;
		}
	}

	////////////////////
	// 화소 영역 처리
	////////////////////
	double mask[5][5] = { {0.0,  0.0, -1.0, 0.0, 0.0}, // LoG 가우시안 마스크
						{0.0, -1.0, -2.0,-1.0, 0.0},
						{-1.0,-2.0, 16.0,-2.0,-1.0},
						{0.0, -1.0, -2.0,-1.0, 0.0},
						{0.0,  0.0, -1.0, 0.0, 0.0} };

	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc2D_double(m_inH + 4, m_inW + 4);
	double** tmpOutImage = OnMalloc2D_double(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값 
	for (int i = 0; i < m_inH + 4; i++)
		for (int k = 0; k < m_inW + 4; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 2][k + 2] = grayImage[i][k];

	// ** 회선 연산 ** 
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3)와 한점을 중심으로 한 3x3을 곱하기
			S = 0.0; // 마스크 25개와 입력값을 각각 곱해서 합한 값.
			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 255;
			else
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree2d(tmpInImage, m_inH + 4);
	OnFree2d(tmpOutImage, m_inH);
	OnFree2d(grayImage, m_inH);
}

void CColorImageProcessingDoc::OnDog()
{
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	unsigned char** grayImage = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) { // GrayScale
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			grayImage[i][k] = (unsigned char)avg;
		}
	}

	////////////////////
	// 화소 영역 처리
	////////////////////
	const int MSIZE = 7;
	double mask[MSIZE][MSIZE]={{0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0}, // DoG 가우시안 마스크
						{0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0},
						{-1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0},
						{-1.0, -3.0, 5.0, 16.0, 5.0, -3.0, -1.0},
						{-1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0},
						{0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0},
						{0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0} };

	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc2D_double(m_inH + MSIZE-1, m_inW + +MSIZE - 1);
	double** tmpOutImage = OnMalloc2D_double(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값 
	for (int i = 0; i < m_inH + MSIZE - 1; i++)
		for (int k = 0; k < m_inW + MSIZE - 1; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 3][k + 3] = grayImage[i][k];

	// ** 회선 연산 ** 
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(7x7)와 한점을 중심으로 한 7x7을 곱하기
			S = 0.0; // 마스크 49개와 입력값을 각각 곱해서 합한 값.
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 255;
			else
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree2d(tmpInImage, m_inH + MSIZE-1);
	OnFree2d(tmpOutImage, m_inH);
	OnFree2d(grayImage, m_inH);
}
/*
void CColorImageProcessingDoc::OnEdgeHomo()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	// 임시 메모리 할당
	const int MSIZE = 3;
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB;
	double** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = (double)m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = (double)m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = (double)m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	int n, m;
	double max;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			max = 0.0; // 블록이 이동할 때마다 최대값 초기화
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					if (fabs(tmpInImageI[i + 1][k + 1] - tmpInImageI[i + n][k + m]) >= max)
						max = fabs(tmpInImageI[i + 1][k + 1] - tmpInImageI[i + n][k + m]);
				}
			}
			tmpInImageI[i][k] = max;
		}
	}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);
}
*/
/*
void CColorImageProcessingDoc::OnEdge1()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {  // 수직 에지 검출 마스크
		{0.0, 0.0, 0.0},
		{-1.0, 1.0, 0.0},
		{0.0,  0.0, 0.0} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	//for (int i = 0; i < m_inH; i++)
	//	for (int k = 0; k < m_inW; k++) {
	//		tmpInImageI[i][k] += 127;
	//	}


	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);
}
*/
/*
void CColorImageProcessingDoc::OnEdgeSub() // HSI
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	// 임시 메모리 할당
	const int MSIZE = 3;
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB;
	double** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = (double)m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = (double)m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = (double)m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double max, temp;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			max = 0.0; // 블록이 이동할 때마다 최대값 초기화
			temp = fabs(tmpInImageI[i][k] - tmpInImageI[i + 2][k + 2]);
			if (temp >= max) max = temp;
			temp = fabs(tmpInImageI[i][k + 1] - tmpInImageI[i + 2][k + 1]);
			if (temp >= max) max = temp;
			temp = fabs(tmpInImageI[i][k + 2] - tmpInImageI[i + 2][k]);
			if (temp >= max) max = temp;
			temp = fabs(tmpInImageI[i + 1][k] - tmpInImageI[i + 1][k + 1]);
			if (temp >= max) max = temp;

			tmpInImageI[i][k] = max;
		}
	}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);
}
*/
/*
void CColorImageProcessingDoc::OnRobert() // HSI
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = { // 로버츠 마스크 행 검출
		{-1.0, 0.0, 0.0},
		{0.0,  1.0, 0.0},
		{0.0,  0.0, 0.0} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	//for (int i = 0; i < m_inH; i++)
	//	for (int k = 0; k < m_inW; k++) {
	//		tmpInImageI[i][k] += 127;
	//	}


	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);

}
*/
/*
void CColorImageProcessingDoc::OnSobel() // HSI
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {  // 소벨 마스크 행 검출
		{-1.0, -2.0, -1.0},
		{0.0,  0.0, 0.0},
		{1.0,  2.0, 1.0} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	//for (int i = 0; i < m_inH; i++)
	//	for (int k = 0; k < m_inW; k++) {
	//		tmpInImageI[i][k] += 127;
	//	}


	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);
}


void CColorImageProcessingDoc::OnLapla() // HSI
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {  // 라플라시안 마스크
		{-1.0, -1.0, -1.0},
		{-1.0,  8.0, -1.0},
		{-1.0, -1.0, -1.0} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	//for (int i = 0; i < m_inH; i++)
	//	for (int k = 0; k < m_inW; k++) {
	//		tmpInImageI[i][k] += 127;
	//	}


	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);
}


void CColorImageProcessingDoc::OnLog()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 5;
	double mask[MSIZE][MSIZE] = { // LoG 가우시안 마스크
		{0.0,  0.0, -1.0, 0.0, 0.0},
		{0.0, -1.0, -2.0,-1.0, 0.0},
		{-1.0,-2.0, 16.0,-2.0,-1.0},
		{0.0, -1.0, -2.0,-1.0, 0.0},
		{0.0,  0.0, -1.0, 0.0, 0.0} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageG = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageB = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);

	tmpInImageH = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageS = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageI = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + MSIZE - 1; i++)
		for (int k = 0; k < m_inW + MSIZE - 1; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 2][k + 2] = m_inImageR[i][k];
			tmpInImageG[i + 2][k + 2] = m_inImageG[i][k];
			tmpInImageB[i + 2][k + 2] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	//for (int i = 0; i < m_inH; i++)
	//	for (int k = 0; k < m_inW; k++) {
	//		tmpInImageI[i][k] += 127;
	//	}


	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageG, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageB, m_inH + MSIZE - 1);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageS, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageI, m_inH + MSIZE - 1);
}


void CColorImageProcessingDoc::OnDog()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 7;
	double mask[MSIZE][MSIZE] = {  // DoG 가우시안 마스크
		{0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0},
		{0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0},
		{-1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0},
		{-1.0, -3.0, 5.0, 16.0, 5.0, -3.0, -1.0},
		{-1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0},
		{0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0},
		{0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageG = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageB = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);

	tmpInImageH = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageS = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);
	tmpInImageI = OnMalloc2D_double(m_inH + MSIZE - 1, m_inW + MSIZE - 1);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + MSIZE - 1; i++)
		for (int k = 0; k < m_inW + MSIZE - 1; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 3][k + 3] = m_inImageR[i][k];
			tmpInImageG[i + 3][k + 3] = m_inImageG[i][k];
			tmpInImageB[i + 3][k + 3] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = (unsigned char)tmpInImageR[i][k]; G = (unsigned char)tmpInImageG[i][k]; B = (unsigned char)tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	//for (int i = 0; i < m_inH; i++)
	//	for (int k = 0; k < m_inW; k++) {
	//		tmpInImageI[i][k] += 127;
	//	}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}

	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageG, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageB, m_inH + MSIZE - 1);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
	OnFree2d(tmpInImageH, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageS, m_inH + MSIZE - 1);
	OnFree2d(tmpInImageI, m_inH + MSIZE - 1);
}
*/



void CColorImageProcessingDoc::OnAccum()
{
	// TODO: 여기에 구현 코드 추가.
	// 효과 누적하기: 현재의 outImage를 inImage로.
	if (m_inW != m_outW) {
		OnFree2d(m_inImageR, m_inH);
		OnFree2d(m_inImageG, m_inH);
		OnFree2d(m_inImageB, m_inH);

		m_inH = m_outH;
		m_inW = m_outW;
		m_inImageR = OnMalloc2D(m_inH, m_inW);
		m_inImageG = OnMalloc2D(m_inH, m_inW);
		m_inImageB = OnMalloc2D(m_inH, m_inW);

	}
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_inImageR[i][k] = m_outImageR[i][k];
			m_inImageG[i][k] = m_outImageG[i][k];
			m_inImageB[i][k] = m_outImageB[i][k];
		}
	}
}


void CColorImageProcessingDoc::OnMorph()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY);
//	int morphH, morphW, inX = 0, inY = 0, morX = 0, morY = 0;

	if (dlg.DoModal() != IDOK)
		return;

//	File.Open(dlg.GetPathName(), CFile::modeRead | CFile::typeBinary);

	OnFreeOutImage();
	CImage image;
	image.Load(dlg.GetPathName());

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = image.GetHeight();
	m_outW = image.GetWidth();
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	m_morImageR = OnMalloc2D(m_outH, m_outW);
	m_morImageG = OnMalloc2D(m_outH, m_outW);
	m_morImageB = OnMalloc2D(m_outH, m_outW);

	// CImage의 객체값 --> 메모리
	COLORREF px;
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			px = image.GetPixel(k, i);
			m_morImageR[i][k] = GetRValue(px);
			m_morImageG[i][k] = GetGValue(px);
			m_morImageB[i][k] = GetBValue(px);

			m_outImageR[i][k] = GetRValue(px);
			m_outImageG[i][k] = GetGValue(px);
			m_outImageB[i][k] = GetBValue(px);
		}

	int morRate = 0;
	double totalNum = 4.0;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if(i >= m_inH || k >= m_inW) { // out of memory

			}
			else {
				m_outImageR[i][k] = (unsigned char)((m_inImageR[i][k] * (totalNum - morRate) / totalNum) + (m_morImageR[i][k] * (morRate) / totalNum));
				m_outImageG[i][k] = (unsigned char)((m_inImageG[i][k] * (totalNum - morRate) / totalNum) + (m_morImageG[i][k] * (morRate) / totalNum));
				m_outImageB[i][k] = (unsigned char)((m_inImageB[i][k] * (totalNum - morRate) / totalNum) + (m_morImageB[i][k] * (morRate) / totalNum));
			}

			// test code start
			m_outImageR[i][k] = (unsigned char)((m_inImageR[i][k] * (totalNum - morRate) / totalNum)
				+ (m_morImageR[i][k] * (morRate) / totalNum));
			// test code end
		}
	}

}
void CColorImageProcessingDoc::OnMorph(int morRate)
{
	double totalNum = 4.0;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (i > m_inH || k > m_inW) { // out of memory

			} 
			else {
				m_outImageR[i][k] = (unsigned char)((m_inImageR[i][k] * (totalNum - morRate) / totalNum) + (m_morImageR[i][k] * (morRate) / totalNum));
				m_outImageG[i][k] = (unsigned char)((m_inImageG[i][k] * (totalNum - morRate) / totalNum) + (m_morImageG[i][k] * (morRate) / totalNum));
				m_outImageB[i][k] = (unsigned char)((m_inImageB[i][k] * (totalNum - morRate) / totalNum) + (m_morImageB[i][k] * (morRate) / totalNum));
			}
		}
	}
	printf("morRate = %d ", morRate);
	if (morRate == 4) {
		OnFree2d(m_morImageR, m_outH);
		OnFree2d(m_morImageG, m_outH);
		OnFree2d(m_morImageB, m_outH);
	}
}



