
// ChildFrm.cpp: CChildFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Gyunity.h"

#include "ChildFrm.h"
#include "SpriteEditorView.h"
#include "SpriteInfoView.h"
#include "DataControl.h"
#include "ExtractedSprite.h"
#include "ControlView.h"
#include "AnimationInfoView.h"
#include "AnimationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CChildFrame 생성/소멸

CChildFrame::CChildFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	/*if (!m_spriteEditor.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("Failed to create view window.\n");
		return;
	}*/
	//if(!m_spriteEditor.Create(nullptr,nullptr,IDD_SPRITE_EDIT, CRect(0,0,))
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서 Window 클래스 또는 스타일을 수정합니다.
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	// 프레임의 윈도우 크기 수정
	cs.cx = 1900;
	cs.cy = 980;
	cs.x = 0;
	cs.y = 0;
	return TRUE;
}

// CChildFrame 진단

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 메시지 처리기


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{


// 	CRect rect = { 0,0,1920,1080 };
// 	//GetClientRect(&amp; rect);
// 	CSize size1(MulDiv(rect.Width(), 20, 100), ::GetSystemMetrics(SM_CYSCREEN)); // 폭(30%)
// 	CSize size2(MulDiv(rect.Width(), 80, 100), ::GetSystemMetrics(SM_CYSCREEN)); // 폭(70%)
// 	CSize size3(MulDiv(rect.Width(), 80, 100), ::GetSystemMetrics(SM_CYSCREEN)); // 폭(70%)
// 
// 	//CSize size11(MulDiv)
// 
// 	// create a splitter with 1 row, 2 columns
// 	if (!m_wndSplitter.CreateStatic(this, 1, 3)) {
// 		TRACE0("Failed to CreateStatic Splitter \n");
// 		return FALSE;
// 	}
// 	// 사용자가 만든 CFormView1 을 좌측에 배치합니다...
// 	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(SpriteEditorView), size1, pContext)) {
// 		TRACE0("Failed to create CFormView1 pane \n");
// 		return FALSE;
// 	}
// 	// 사용자가 만든 CFormView2 을 우측에 배치합니다...
// 	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CGyunityView), size2, pContext)) {
// 		TRACE0("Failed to create CFormView2 pane \n");
// 		return FALSE;
// 	}
// 	if (!m_wndSplitter.CreateView(0, 2, RUNTIME_CLASS(SpriteInfoView), size3, pContext))
// 	{
// 		TRACE0("Failed to create CFormView3 pane \n");
// 		return FALSE;
// 	}
// 	return TRUE;

	//////////////////////////////////////////////////////////////////////////


	if (!m_wndSplitter.CreateStatic(this, 1, 3))
	{
		TRACE0("Failed to CreateStatic Splitter\n");
		return FALSE;
	}
	int m_IDpane = m_wndSplitter.IdFromRowCol(0, 0); //왼쪽 윈도우 아이디 접근
	int m_IDpane2 = m_wndSplitter.IdFromRowCol(0, 1); //중간 윈도우 아이디 접근
	int m_IDpane3 = m_wndSplitter.IdFromRowCol(0, 2); //오른쪽 윈도우 아이디 접근

	if (!m_wndSplitter2.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_IDpane))
	{
		TRACE0("Failed to CreateStatic Splitter2\n");
		return FALSE;
	}

	if (!m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(SpriteEditorView), CSize(200, 10), pContext)
		|| !m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(SpriteInfoView), CSize(200, 10), pContext))
	{
		TRACE0("Fail to create Left view");
		return FALSE;
	}

	/*if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CGyunityView), CSize(800, 200), pContext))
	{
		TRACE0("Fail to create CGyunityView");
		return FALSE;
	}*/


	if (!m_wndSplitter3.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_IDpane2))
	{
		TRACE0("Failed to CreateStatic Splitter2\n");
		return FALSE;
	}
	if (!m_wndSplitter3.CreateView(0, 0, RUNTIME_CLASS(CGyunityView), CSize(800, 800), pContext))
	{
		TRACE0("Fail to create CGyunityView");
		return FALSE;
	}
	//
	if (!m_wndSplitter3.CreateView(1, 0, RUNTIME_CLASS(ControlView), CSize(800, 200), pContext))
	{
		TRACE0("Fail to create ControlView");
		return FALSE;
	}
// 	if (!m_wndSplitter.CreateView(0, 2, RUNTIME_CLASS(AnimationInfoView), CSize(1200, 1200), pContext))
// 	{
// 		TRACE0("Fail to create AnimationInfoView");
// 		return FALSE;
// 	}

	if (!m_wndSplitter4.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_IDpane3))
	{
		TRACE0("Fail to create m_wndSplitter4");
		return FALSE;
	}
	if (!m_wndSplitter4.CreateView(0, 0, RUNTIME_CLASS(AnimationInfoView), CSize(1200, 1200), pContext))
	{
		TRACE0("Fail to create AnimationInfoView");
		return FALSE;
	}
	if (!m_wndSplitter4.CreateView(1, 0, RUNTIME_CLASS(AnimationView), CSize(1200, 1200), pContext))
	{
		TRACE0("Fail to create AnimationView");
		return FALSE;
	}

// 	if (!m_wndSplitter4.CreateView(0, 0, RUNTIME_CLASS(AnimationInfoView), CSize(200, 200), pContext))
// 	{
// 		TRACE0("Fail to create AnimationInfoView");
// 		return FALSE;
// 	}


	// splitter 정보 변경 ( 행or 열 , 최대 크기, 최소 크기)
	m_wndSplitter.SetColumnInfo(0, 250, 20);
	m_wndSplitter.SetColumnInfo(1, 1400, 20);
	m_wndSplitter2.SetRowInfo(0, 500, 10);
	m_wndSplitter4.SetRowInfo(0, 500, 10);

	//m_wndSplitter4.SetColumnInfo()

	return TRUE;


	//return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}