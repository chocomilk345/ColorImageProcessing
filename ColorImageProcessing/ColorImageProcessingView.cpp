
// ColorImageProcessingView.cpp: CColorImageProcessingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageProcessing.h"
#endif

#include "ColorImageProcessingDoc.h"
#include "ColorImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorImageProcessingView

IMPLEMENT_DYNCREATE(CColorImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CColorImageProcessingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CColorImageProcessingView::OnEqualImage)
	ON_COMMAND(IDM_GRAY_SCALE, &CColorImageProcessingView::OnGrayScale)
	ON_COMMAND(IDM_ADD_IMAGE, &CColorImageProcessingView::OnAdd)
	ON_COMMAND(IDM_MUL_IMAGE, &CColorImageProcessingView::OnMul)
	ON_COMMAND(IDM_DIV_IMAGE, &CColorImageProcessingView::OnDiv)
	ON_COMMAND(IDM_AND_IMAGE, &CColorImageProcessingView::OnAnd)
	ON_COMMAND(IDM_OR_IMAGE, &CColorImageProcessingView::OnOr)
	ON_COMMAND(IDM_XOR_IMAGE, &CColorImageProcessingView::OnXor)
	ON_COMMAND(IDM_REV_IMAGE, &CColorImageProcessingView::OnRev)
	ON_COMMAND(IDM_BW_IMAGE, &CColorImageProcessingView::OnBw)
	ON_COMMAND(IDM_BW_AVG_IMAGE, &CColorImageProcessingView::OnBwAvg)
	ON_COMMAND(IDM_BW_MED_IMAGE, &CColorImageProcessingView::OnBwMed)
	ON_COMMAND(IDM_GAMMA_IMAGE, &CColorImageProcessingView::OnGamma)
	ON_COMMAND(IDM_PARA_IMAGE, &CColorImageProcessingView::OnPara)
	ON_COMMAND(IDM_PARA2_IMAGE, &CColorImageProcessingView::OnPara2)
	ON_COMMAND(IDM_POST_IMAGE, &CColorImageProcessingView::OnPost)
	ON_COMMAND(IDM_STRESS_IMAGE, &CColorImageProcessingView::OnStress)
	ON_COMMAND(IDM_CHANGE_SATUR, &CColorImageProcessingView::OnChangeSatur)
	ON_COMMAND(IDM_PICK_ORANGE, &CColorImageProcessingView::OnPickOrange)
	ON_COMMAND(IDM_MOV_IMAGE, &CColorImageProcessingView::OnMov)
	ON_COMMAND(IDM_MIR_HOR_IMAGE, &CColorImageProcessingView::OnMirHor)
	ON_COMMAND(IDM_ZOOMIN_IMAGE, &CColorImageProcessingView::OnZoomin)
	ON_COMMAND(IDM_ZOOMIN2_IMAGE, &CColorImageProcessingView::OnZoomin2)
	ON_COMMAND(IDM_ZOOMIN3_IMAGE, &CColorImageProcessingView::OnZoomin3)
	ON_COMMAND(IDM_ZOOMOUT_IMAGE, &CColorImageProcessingView::OnZoomout)
	ON_COMMAND(IDM_ZOOMOUT_AVG_IMAGE, &CColorImageProcessingView::OnZoomoutAvg)
	ON_COMMAND(IDM_ZOOMOUT_MED_IMAGE, &CColorImageProcessingView::OnZoomoutMed)
	ON_COMMAND(IDM_ROTATE_IMAGE, &CColorImageProcessingView::OnRotate)
	ON_COMMAND(IDM_ROTATE2_IMAGE, &CColorImageProcessingView::OnRotate2)
	ON_COMMAND(IDM_ROTATE3_IMAGE, &CColorImageProcessingView::OnRotate3)
	ON_COMMAND(IDM_MIR_VER_IMAGE, &CColorImageProcessingView::OnMirVer)
	ON_COMMAND(IDM_HISTRO_STRETCH_IMAGE, &CColorImageProcessingView::OnHistroStretch)
	ON_COMMAND(IDM_ENDIN_IMAGE, &CColorImageProcessingView::OnEndin)
	ON_COMMAND(IDM_HISTO_EQUAL_IMAGE, &CColorImageProcessingView::OnHistoEqual)
	ON_COMMAND(IDM_EMBOSS_IMAGE, &CColorImageProcessingView::OnEmboss)
	ON_COMMAND(IDM_BLUR_IMAGE, &CColorImageProcessingView::OnBlur)
	ON_COMMAND(IDM_BLUR2_IMAGE, &CColorImageProcessingView::OnBlur2)
	ON_COMMAND(IDM_SHARP_IMAGE, &CColorImageProcessingView::OnSharp)
	ON_COMMAND(IDM_EDGE1_IMAGE, &CColorImageProcessingView::OnEdge1)
	ON_COMMAND(IDM_EDGE_HOMO_IMAGE, &CColorImageProcessingView::OnEdgeHomo)
	ON_COMMAND(IDM_EDGE_SUB_IMAGE, &CColorImageProcessingView::OnEdgeSub)
	ON_COMMAND(IDM_ROBERT_IMAGE, &CColorImageProcessingView::OnRobert)
	ON_COMMAND(IDM_SOBEL_IMAGE, &CColorImageProcessingView::OnSobel)
	ON_COMMAND(IDM_LAPLA_IMAGE, &CColorImageProcessingView::OnLapla)
	ON_COMMAND(IDM_LOG_IMAGE, &CColorImageProcessingView::OnLog)
	ON_COMMAND(IDM_DOG_IMAGE, &CColorImageProcessingView::OnDog)
	ON_COMMAND(IDM_EMBOSS_HSI, &CColorImageProcessingView::OnEmbossHsi)
	ON_COMMAND(IDM_SHARP_HPF, &CColorImageProcessingView::OnSharpHpf)
	ON_COMMAND(IDM_ACCUM, &CColorImageProcessingView::OnAccum)
	ON_COMMAND(IDM_MORPH_IMAGE, &CColorImageProcessingView::OnMorph)
	ON_WM_TIMER()
	ON_COMMAND(IDM_SATUR_ADD, &CColorImageProcessingView::OnSaturAdd)
	ON_COMMAND(IDM_SATUR_SUB, &CColorImageProcessingView::OnSaturSub)
	ON_COMMAND(IDM_CHANGE_INTEN, &CColorImageProcessingView::OnChangeInten)
	ON_COMMAND(IDM_CHANGE_COLOR, &CColorImageProcessingView::OnChangeColor)
END_MESSAGE_MAP()

// CColorImageProcessingView 생성/소멸

CColorImageProcessingView::CColorImageProcessingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CColorImageProcessingView::~CColorImageProcessingView()
{
}

BOOL CColorImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CColorImageProcessingView 그리기

void CColorImageProcessingView::OnDraw(CDC* pDC)
{
	//CColorImageProcessingDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	//// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//int R, G, B;
	//for (int i = 0; i < pDoc->m_inH; i++)
	//	for (int k = 0; k < pDoc->m_inW; k++) {
	//		R = pDoc->m_inImageR[i][k];
	//		G = pDoc->m_inImageG[i][k];
	//		B = pDoc->m_inImageB[i][k];
	//		pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
	//	}

	//for (int i = 0; i < pDoc->m_outH; i++)
	//	for (int k = 0; k < pDoc->m_outW; k++) {
	//		R = pDoc->m_outImageR[i][k];
	//		G = pDoc->m_outImageG[i][k];
	//		B = pDoc->m_outImageB[i][k];
	//		pDC->SetPixel(pDoc->m_inW + k + 5 + 5, i + 5, RGB(R, G, B));
	//	}

	///////////////////
	/// ** 화면 크기 조절 **
	///////////////////
	// 
	///////////////////
	/// ** 더블 버퍼링 **
	///////////////////
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/////////////////////
	/// 성능 개선을 위한 더블 버퍼링 
	////////////////////
	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	// 출력 영상의 크기를 자동 조절
	double MAXSIZE = 800; // 필요시 실 모니터 또는 화면의 해상도에 따라서 변경 가능!
	int inH = pDoc->m_inH;
	int inW = pDoc->m_inW;
	double hop = 1.0; // 기본
	if (inH > MAXSIZE || inW > MAXSIZE) {
		// hop을 새로 계산.
		if (inW > inH)
			hop = (inW / MAXSIZE);
		else
			hop = (inH / MAXSIZE);

		inW = (int)(inW / hop);
		inH = (int)(inH / hop);
	}
	
	// 메모리 DC에 그리기
	for (i = 0; i < inH; i++) {
		for (k = 0; k < inW; k++) {
			R = pDoc->m_inImageR[(int)(i*hop)][(int)(k*hop)];
			G = pDoc->m_inImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_inImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	int outH = pDoc->m_outH;
	int outW = pDoc->m_outW;
	hop = 1.0; // 기본
	if (outH > MAXSIZE || outW > MAXSIZE) {
		// hop을 새로 계산.
		if (outW > outH)
			hop = (outW / MAXSIZE);
		else
			hop = (outH / MAXSIZE);

		outW = (int)(outW / hop);
		outH = (int)(outH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < outH; i++) {
		for (k = 0; k < outW; k++) {
			R = pDoc->m_outImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_outImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_outImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
	/*
	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_inH; i++) {
		for (k = 0; k < pDoc->m_inW; k++) {
			R = pDoc->m_inImageR[i][k];
			G = pDoc->m_inImageG[i][k];
			B = pDoc->m_inImageB[i][k];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_outH; i++) {
		for (k = 0; k < pDoc->m_outW; k++) {
			R = pDoc->m_outImageR[i][k];
			G = pDoc->m_outImageG[i][k];
			B = pDoc->m_outImageB[i][k];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(pDoc->m_inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
	*/
}


// CColorImageProcessingView 인쇄

BOOL CColorImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CColorImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CColorImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CColorImageProcessingView 진단

#ifdef _DEBUG
void CColorImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CColorImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorImageProcessingDoc* CColorImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorImageProcessingDoc)));
	return (CColorImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CColorImageProcessingView 메시지 처리기


void CColorImageProcessingView::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnGrayScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGrayScale();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAdd();
	Invalidate(TRUE); // OnDraw() 호출 효과	
}


void CColorImageProcessingView::OnMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMul();
	Invalidate(TRUE); // OnDraw() 호출 효과	
}


void CColorImageProcessingView::OnDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDiv();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnAnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAnd();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnOr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOr();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnXor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnXor();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnRev()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRev();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnBw()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBw();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnBwAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBwAvg();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnBwMed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBwMed();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnGamma()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGamma();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnPara()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPara();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnPara2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPara2();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnPost()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPost();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnStress()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnStress();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnChangeSatur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeSatur();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnPickOrange()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPickOrange();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnMov()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMov();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnMirHor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirHor();
	Invalidate(TRUE); // OnDraw() 호출 효과
}

void CColorImageProcessingView::OnMirVer()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirVer();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnZoomin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomin();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnZoomin2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomin2();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnZoomin3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomin3();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnZoomout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomout();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnZoomoutAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomoutAvg();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnZoomoutMed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomoutMed();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnRotate2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate2();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnRotate3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate3();
	Invalidate(TRUE); // OnDraw() 호출 효과
}




void CColorImageProcessingView::OnHistroStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistroStretch();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnEndin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndin();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnEmboss()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmboss();
	Invalidate(TRUE); // OnDraw() 호출 효과
}

void CColorImageProcessingView::OnEmbossHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossHsi();
	Invalidate(TRUE); // OnDraw() 호출 효과
}

void CColorImageProcessingView::OnBlur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlur();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnBlur2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlur2();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharp();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnSharpHpf()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpHpf();
	Invalidate(TRUE); // OnDraw() 호출 효과
}

void CColorImageProcessingView::OnEdge1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge1();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnEdgeHomo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeHomo();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnEdgeSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeSub();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnRobert()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRobert();
	Invalidate(TRUE); // OnDraw() 호출 효과

}


void CColorImageProcessingView::OnSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSobel();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnLapla()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLapla();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnLog()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLog();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnDog()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDog();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnAccum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAccum();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnMorph()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	m_nMorph = 0;
	pDoc->OnMorph();

	Invalidate(TRUE); // OnDraw() 호출 효과
	SetTimer(5, 2000, NULL);

}


void CColorImageProcessingView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 5) {
		m_nMorph++;

		CColorImageProcessingDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnMorph(m_nMorph);
		CRect r = { pDoc->m_inW + 10, 5, pDoc->m_inW + 10 + pDoc->m_outW, 5 + pDoc->m_outH };
		InvalidateRect(&r, TRUE); // OnDraw() 호출 효과

		if (m_nMorph == 4) {
			KillTimer(5);
		}
	}
	CView::OnTimer(nIDEvent);
}


void CColorImageProcessingView::OnSaturAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSaturAdd();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnSaturSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSaturSub();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnChangeInten()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeInten();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CColorImageProcessingView::OnChangeColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeColor();
	Invalidate(TRUE); // OnDraw() 호출 효과
}
