
// ColorImageProcessingView.h: CColorImageProcessingView 클래스의 인터페이스
//

#pragma once


class CColorImageProcessingView : public CView
{
protected: // serialization에서만 만들어집니다.
	CColorImageProcessingView() noexcept;
	DECLARE_DYNCREATE(CColorImageProcessingView)

// 특성입니다.
public:
	CColorImageProcessingDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CColorImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnGrayScale();
	afx_msg void OnAdd();
	afx_msg void OnMul();
	afx_msg void OnDiv();
	afx_msg void OnAnd();
	afx_msg void OnOr();
	afx_msg void OnXor();
	afx_msg void OnRev();
	afx_msg void OnBw();
	afx_msg void OnBwAvg();
	afx_msg void OnBwMed();
	afx_msg void OnGamma();
	afx_msg void OnPara();
	afx_msg void OnPara2();
	afx_msg void OnPost();
	afx_msg void OnStress();
	afx_msg void OnChangeSatur();
	afx_msg void OnPickOrange();
	afx_msg void OnMov();
	afx_msg void OnMirHor();
	afx_msg void OnZoomin();
	afx_msg void OnZoomin2();
	afx_msg void OnZoomin3();
	afx_msg void OnZoomout();
	afx_msg void OnZoomoutAvg();
	afx_msg void OnZoomoutMed();
	afx_msg void OnRotate();
	afx_msg void OnRotate2();
	afx_msg void OnRotate3();
	afx_msg void OnMirVer();
	afx_msg void OnHistroStretch();
	afx_msg void OnEndin();
	afx_msg void OnHistoEqual();
	afx_msg void OnEmboss();
	afx_msg void OnBlur();
	afx_msg void OnBlur2();
	afx_msg void OnSharp();
	afx_msg void OnEdge1();
	afx_msg void OnEdgeHomo();
	afx_msg void OnEdgeSub();
	afx_msg void OnRobert();
	afx_msg void OnSobel();
	afx_msg void OnLapla();
	afx_msg void OnLog();
	afx_msg void OnDog();
	afx_msg void OnEmbossHsi();
	afx_msg void OnSharpHpf();
	afx_msg void OnAccum();
	afx_msg void OnMorph();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_nMorph;
	afx_msg void OnSaturAdd();
	afx_msg void OnSaturSub();
	afx_msg void OnChangeInten();
	afx_msg void OnChangeColor();
};

#ifndef _DEBUG  // ColorImageProcessingView.cpp의 디버그 버전
inline CColorImageProcessingDoc* CColorImageProcessingView::GetDocument() const
   { return reinterpret_cast<CColorImageProcessingDoc*>(m_pDocument); }
#endif

