
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "GyunityMapTool.h"
#include "GyunityMapToolDoc.h"

#include "MainFrm.h"

#include "MapManagerView.h"
#include "MapBrushView.h"
#include "GyunityMapToolView.h"
#include "NPCManagerView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if (!m_wndSplitter.CreateStatic(this, 1, 3))
	{
		TRACE0("Failed to create m_wndSplitter!\n");
		return FALSE;
	}
	if (!m_wndSplitter2.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 0)))
	{
		TRACE0("Failed to create m_wndSplitter2!\n");
		return FALSE;
	}
	if (!m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(MapManagerView), CSize(200, 10), pContext))
	{
		TRACE0("Failed to create MapManagerView!\n");
		return FALSE;
	}
	if (!m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(MapBrushView), CSize(200, 10), pContext))
	{
		TRACE0("Failed to create MapBrushView!\n");
		return FALSE;
	}
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CGyunityMapToolView), CSize(200, 10), pContext))
	{
		TRACE0("Failed to create CGyunityMapToolView!\n");
		return FALSE;
	}
	if (!m_wndSplitter.CreateView(0, 2, RUNTIME_CLASS(NPCManagerView), CSize(200, 10), pContext))
	{
		TRACE0("Failed to create NPCManagerView!\n");
		return FALSE;
	}
// 	if (!m_wndSplitter3.CreateStatic(&m_wndSplitter, 1, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 2)))
// 	{
// 		TRACE0("Failed to create m_wndSplitter3!\n");
// 		return FALSE;
// 	}
// 	if (!m_wndSplitter3.CreateView(0, 0, RUNTIME_CLASS(NPCManagerView), CSize(200, 10), pContext))
// 	{
// 		TRACE0("Failed to create NPCManagerView!\n");
// 		return FALSE;
// 	}

	m_wndSplitter.SetColumnInfo(0, 400, 20);
	m_wndSplitter.SetColumnInfo(1, 1000, 20);
	m_wndSplitter2.SetRowInfo(0, 600, 20);

	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
