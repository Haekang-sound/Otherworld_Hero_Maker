
// GyunityMapToolView.cpp: CGyunityMapToolView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GyunityMapTool.h"
#endif

#include "GyunityMapToolDoc.h"
#include "GyunityMapToolView.h"

#include "Global.h"
#include "DataControl.h"
#include "TileManager.h"

#include "Tile.h"
#include "TileBrush.h"
#include "Grid.h"
#include "NPCGrid.h"
#include "ResourceManager.h"
#include "MapBrushView.h"

#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGyunityMapToolView

IMPLEMENT_DYNCREATE(CGyunityMapToolView, CView)

BEGIN_MESSAGE_MAP(CGyunityMapToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_EDIT_UNDO, &CGyunityMapToolView::OnEditUndo)
	ON_COMMAND(ID_REDO, &CGyunityMapToolView::OnRedo)
END_MESSAGE_MAP()

// CGyunityMapToolView 생성/소멸

CGyunityMapToolView::CGyunityMapToolView() noexcept
{
	D2DInitialize();
	Initialize();
}

CGyunityMapToolView::~CGyunityMapToolView()
{
	delete m_groundGrid;
	delete m_mapGrid;
	delete m_npcGrid;
	delete m_tileBrush;
}

BOOL CGyunityMapToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGyunityMapToolView 그리기

void CGyunityMapToolView::OnDraw(CDC* /*pDC*/)
{
	CGyunityMapToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	GetDocument()->m_mainView = this;

	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Pink));

	if (m_groundGrid->GetBaseTile() != nullptr)
	{
		if (m_OnGround)
		{
			DrawGroundGrid();
		}
	}

	if (m_npcGrid->GetBaseTile() != nullptr)
	{
		if (m_OnNPCLayer)
		{
			DrawNPCLayerGrid();
		}
	}

	if (m_mapGrid->GetBaseTile() != nullptr)
	{
		if (m_OnMap)
		{
			DrawMapGrid();
		}
	}

	GetDocument()->GetDataControl()->SetRenderTarget(GetRenderTarget());
	m_pRenderTarget->EndDraw();

	static bool isFirst = false;
	if (!isFirst)
	{
		std::wstring path = L"../GyunityMapTool/resource/TileData.txt";
		pDoc->GetDataControl()->LoadTile(path.c_str());
		pDoc->m_mapBrushView->RefreshTile();
		isFirst = true;
	}
}


// CGyunityMapToolView 인쇄

BOOL CGyunityMapToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGyunityMapToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGyunityMapToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGyunityMapToolView 진단

#ifdef _DEBUG
void CGyunityMapToolView::AssertValid() const
{
	CView::AssertValid();
}

void CGyunityMapToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG
void CGyunityMapToolView::D2DInitialize()
{
	EnableD2DSupport();

	m_pRenderTarget;
	// 브러쉬 초기화
	m_gridBrush = new CD2DSolidColorBrush(GetRenderTarget(), D2D1::ColorF(D2D1::ColorF::Green));
}

void CGyunityMapToolView::Initialize()
{
	m_groundGrid = new Grid();
	m_mapGrid = new Grid();
	m_npcGrid = new NPCGrid();
	m_tileBrush = new TileBrush();

	// 렌더 타겟 저장
	// GetDocument()->GetDataControl()->SetRenderTarget(GetRenderTarget());

	/*std::wstring path = ResourceManager::GetInstance().GetImagePath(L"base.png");

	Tile* baseTile = new Tile();
	CD2DBitmap* baseTileBitmap = LoadBitmapByFilePath(path.c_str());
	baseTile->SetBitmap(baseTileBitmap);
	m_grid->SetBaseTile(baseTile);*/

}

void CGyunityMapToolView::SetScreenScale(INT parameter, CPoint mousePos)
{
	//return;
	//
	if (parameter > 0)
	{
		m_gridScale += 0.02f;
		//m_currentPos -= 400.f;
	}
	else if (parameter < 0)
	{
		m_gridScale -= 0.02f;
		//m_currentPos += 400.f;
	}

	if (m_gridScale <= 0)
	{
		m_gridScale = 0;
		return;
	}
	//g_CameraPos = D2D1::Matrix3x2F::Scale(m_gridScale, m_gridScale) * D2D1::Matrix3x2F::Translation(g_CameraPos.dx,g_CameraPos.dy);
	g_CameraPos = D2D1::Matrix3x2F::Translation(g_CameraPos.dx,g_CameraPos.dy);
	
	g_Scale = m_gridScale;

	Invalidate();

	//CString s;
	//s.Format(_T("%d, %d"), screenPt.x, screenPt.y);
	//MessageBox(s);

	return;
}

CD2DBitmap* CGyunityMapToolView::LoadBitmapByFilePath(CString filePath)
{
	HINSTANCE hResInstance = AfxGetResourceHandle();
	m_pRenderTarget;
	CD2DBitmap* newBitmap = new CD2DBitmap(GetRenderTarget(), filePath, CD2DSizeU(0, 0), TRUE);
	newBitmap->Create(GetRenderTarget());
	AfxSetResourceHandle(hResInstance);
	return newBitmap;
}

COLORREF CGyunityMapToolView::GetPixelColorFromBitmap(CBitmap* bitmap, int x, int y)
{
	CDC dc;
	dc.CreateCompatibleDC(nullptr);
	CBitmap* oldBitmap = dc.SelectObject(bitmap);
	COLORREF color = dc.GetPixel(x, y);
	dc.SelectObject(oldBitmap);
	dc.DeleteDC();

	return color;
}

void CGyunityMapToolView::SetCurrentTile(Tile* tile)
{
	m_tileBrush->SetTile(tile);
}

void CGyunityMapToolView::DrawGroundGrid()
{
	m_groundGrid->Render(m_pRenderTarget);
}

void CGyunityMapToolView::DrawMapGrid()
{
	m_mapGrid->Render(m_pRenderTarget);
}

void CGyunityMapToolView::DrawNPCLayerGrid()
{
	m_npcGrid->Render(m_pRenderTarget);
}

CGyunityMapToolDoc* CGyunityMapToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	return reinterpret_cast<CGyunityMapToolDoc*>(m_pDocument);

	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGyunityMapToolDoc)));
	return (CGyunityMapToolDoc*)m_pDocument;
}


// CGyunityMapToolView 메시지 처리기


void CGyunityMapToolView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 여기서 안쓰고 PreTranslateMessage에서 함
	CView::OnMouseHWheel(nFlags, zDelta, pt);
}


BOOL CGyunityMapToolView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_MOUSEWHEEL)
	{
		// pMsg->wParam이 양수일 때 위로 회전
		// 음수일 때 아래로 회전
//  		CString s;
//  		s.Format(_T("%d"), );
// 		MessageBox(s); 

		CPoint mousePos(GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam));

		SetScreenScale(pMsg->wParam, mousePos);
	}

	if (pMsg->message == WM_LBUTTONDOWN)
	{
		//if()
		m_isLMouseClicked = true;
		switch (GetGridType())
		{
			case GridType::Ground:
				if (m_tileType == TileType::NPC)
				{
					MessageBox(_T("왼쪽 브러쉬를 선택하세요"));
					m_isLMouseClicked = false;
					break;
				}
				m_groundGrid->SetTilePosByMouseClicked(m_tileIndex);
				break;
			case GridType::Map:
				if (m_tileType == TileType::NPC)
				{
					MessageBox(_T("왼쪽 브러쉬를 선택하세요"));
					m_isLMouseClicked = false;
					break;
				}
				m_mapGrid->SetTilePosByMouseClicked(m_tileIndex);
				break;
			case GridType::NPC:
				if (m_tileType == TileType::World)
				{
					MessageBox(_T("오른쪽 브러쉬를 선택하세요"));
					m_isLMouseClicked = false;
					break;
				}
				m_npcGrid->SetTilePosByMouseClicked(m_tileIndex);
				break;
			default:
				break;
		}
		// m_mapGrid->SetTilePosByMouseClicked(m_tileIndex);

		Invalidate();
		// 		CPoint mousePos(GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam));
		// 		POINT screenPt;
		// 		GetCursorPos(&screenPt);
		// 
		// 
		// 		::ScreenToClient(GetRenderTarget()->GetHwnd(), &screenPt);
		// 		CString s;
		// 		s.Format(_T("%d, %d"), screenPt.x, screenPt.y);
		// 		MessageBox(s);
	}
	if (pMsg->message == WM_LBUTTONUP)
	{
		m_isLMouseClicked = false;
	}

	if (pMsg->message == WM_RBUTTONDOWN)
	{
		m_isRMouseClicked = true;
		CPoint mousePos(GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam));
		//ScreenToClient(&mousePos);
		m_prevMousePos = mousePos;
		//m_prevMousePos.x += g_CameraPos.dx;
		//m_prevMousePos.y += g_CameraPos.dy;

		m_prevMousePos.x = mousePos.x - g_CameraPos.dx;
		m_prevMousePos.y = mousePos.y - g_CameraPos.dy;
	}

	if (pMsg->message == WM_RBUTTONUP)
	{
		m_isRMouseClicked = false;
	}
	return CView::PreTranslateMessage(pMsg);
}


void CGyunityMapToolView::DoDataExchange(CDataExchange* pDX)
{
	GetDocument()->m_mainView = this;
	CView::DoDataExchange(pDX);
}


void CGyunityMapToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mapGrid->SetMousePoint(point);
	m_groundGrid->SetMousePoint(point);
	m_npcGrid->SetMousePoint(point);
	if (m_isLMouseClicked)
	{
		//m_grid->m_mouseClicked = true;
		switch (GetGridType())
		{
			case GridType::Ground:
				m_groundGrid->SetTilePosByMouseClicked(m_tileIndex);
				break;
			case GridType::Map:
				m_mapGrid->SetTilePosByMouseClicked(m_tileIndex);
				break;
			case GridType::NPC:
				m_npcGrid->SetTilePosByMouseClicked(m_tileIndex);
				break;
			default:
				break;
		}
	}

	if (m_isRMouseClicked)
	{
		//CPoint mousePos(GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam));
		//ScreenToClient(&mousePos);
		CString s;
		s.Format(_T("%d, %d"), point.x, point.y);
		//MessageBox(s);
		//MessageBox(s);
		//g_CameraPos.x +=
		float moveX = point.x - m_prevMousePos.x;
		float moveY = point.y - m_prevMousePos.y;

		//g_CameraPos = g_CameraPos * D2D1::Matrix3x2F::Translation(moveX, moveY);
		g_CameraPos = D2D1::Matrix3x2F::Translation(moveX, moveY);

	}

	Invalidate();
	CView::OnMouseMove(nFlags, point);
}


void CGyunityMapToolView::OnEditUndo()
{
	MessageBox(_T("안만들었지롱"));
}


void CGyunityMapToolView::OnRedo()
{
	MessageBox(_T("히히"));
}


void CGyunityMapToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//std::wstring path = L"../GyunityMapTool/resource/TileData.txt";
	//GetDocument()->GetDataControl()->LoadTile(path.c_str());
}
