
// ResourceManagerToolView.cpp: CResourceManagerToolView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ResourceManagerTool.h"
#endif
#include "ResourceManagerToolDoc.h"
#include "ResourceManagerToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CResourceManagerToolView

IMPLEMENT_DYNCREATE(CResourceManagerToolView, CView)

BEGIN_MESSAGE_MAP(CResourceManagerToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

// CResourceManagerToolView 생성/소멸

CResourceManagerToolView::CResourceManagerToolView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CResourceManagerToolView::~CResourceManagerToolView()
{
}

BOOL CResourceManagerToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CResourceManagerToolView 그리기

void CResourceManagerToolView::OnDraw(CDC* /*pDC*/)
{
	CResourceManagerToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CResourceManagerToolView 인쇄

BOOL CResourceManagerToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CResourceManagerToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CResourceManagerToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CResourceManagerToolView 진단

#ifdef _DEBUG
void CResourceManagerToolView::AssertValid() const
{
	CView::AssertValid();
}

void CResourceManagerToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CResourceManagerToolDoc* CResourceManagerToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CResourceManagerToolDoc)));
	return (CResourceManagerToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CResourceManagerToolView 메시지 처리기


int CResourceManagerToolView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	DragAcceptFiles(TRUE);
	return 0;
}


void CResourceManagerToolView::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TCHAR szFullFilePath[_MAX_PATH];
	int TotalFiles = ::DragQueryFile(hDropInfo, 0xFFFFFFFF, szFullFilePath, _MAX_PATH);

	// 이제 갯수를 알 수 있다.
	for (int i = 0; i < TotalFiles; i++)
	{
		// 드롭된 갯수만큼 실행한다.
		::DragQueryFile(hDropInfo, i, szFullFilePath, _MAX_PATH);
		
		// 테스트용
		AfxMessageBox(szFullFilePath);
		// 각각의 파일네임을 가져왔음, 이제 마음대로 사용.

		// 나만의 코드를 실행..

	}

	// 끝.
	::DragFinish(hDropInfo);
	CView::OnDropFiles(hDropInfo);
}
