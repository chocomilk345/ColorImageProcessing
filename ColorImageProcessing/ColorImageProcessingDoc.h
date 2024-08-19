
// ColorImageProcessingDoc.h: CColorImageProcessingDoc 클래스의 인터페이스
//


#pragma once
#include <iostream>

class CColorImageProcessingDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CColorImageProcessingDoc() noexcept;
	DECLARE_DYNCREATE(CColorImageProcessingDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CColorImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;
	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;

	unsigned char** m_morImageR = NULL;
	unsigned char** m_morImageG = NULL;
	unsigned char** m_morImageB = NULL;

	int m_inH = 0;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	unsigned char** OnMalloc2D(int h, int w);
	double** OnMalloc2D_double(int h, int w);
	double** OnMalloc2D(int h, int w, double initVal);
//	void OnFree2d(unsigned char** memory, int h);
//	void OnFree2d(double** memory, int h);
	template <typename T>
	void OnFree2d(T** memory, int h);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnEqualImage();
	virtual void OnCloseDocument();
	void OnFreeOutImage();
	void OnGrayScale();
	void OnAdd();
	void OnMul();
	void OnDiv();
	void OnAnd();
	void OnOr();
	void OnXor();
	void OnRev();
	void OnBw();
	void OnBwAvg();
	void OnBwMed();
	void OnGamma();
	void OnPara();
	void OnPara2();
	void OnPost();
	void OnStress();
	void OnChangeSatur();
	double* RGB2HSI(int R, int G, int B);
	unsigned char* HSI2RGB(double H, double S, double I);
	void OnPickOrange();
	void OnMov();
	void OnMirHor();
	void OnMirVer();
	void OnZoomin();
	void OnZoomin2();
	void OnZoomin3();
	void OnZoomout();
	void OnZoomoutAvg();
	void OnZoomoutMed();
	void OnRotate();
	void OnRotate2();
	void OnRotate3();
	void OnHistroStretch();
	void OnEndin();
	void OnHistoEqual();
	void OnEmboss();
	void OnBlur();
	void OnBlur2();
	void OnSharp();
	void OnEdge1();
	void OnEdgeHomo();
	void OnEdgeSub();
	void OnRobert();
	void OnSobel();
	void OnLapla();
	void OnLog();
	void OnDog();
	void OnEmbossHsi();

	void OnSharpHpf();
	void OnAccum();
	void OnMorph();
	void OnMorph(int val);

	void OnSaturAdd();
	void OnSaturSub();
	void OnChangeInten();
	void OnChangeColor();
};
