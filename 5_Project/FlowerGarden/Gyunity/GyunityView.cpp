#pragma once
// GyunityView.cpp: CGyunityView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Gyunity.h"
#endif

#include "GyunityDoc.h"
#include "GyunityView.h"
#include "SpriteInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static int nAnimationGroup = 0;
static int nInfoAreaHeight = 40;

// CGyunityView

IMPLEMENT_DYNCREATE(CGyunityView, CView)

BEGIN_MESSAGE_MAP(CGyunityView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	//	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_New_Image, &CGyunityView::OnNewImage)
	ON_WM_SIZE()
	//	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &CGyunityView::OnDraw2D)
	//	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_Animation_Play, &CGyunityView::OnAnimationPlay)
	ON_COMMAND(ID_Animation_ReversePlay, &CGyunityView::OnAnimationReverseplay)
	ON_COMMAND(ID_Animation_Stop, &CGyunityView::OnAnimationStop)
	//	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CGyunityView 생성/소멸

CGyunityView::CGyunityView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	MyInitialize();
	m_isClicked = false;
	m_selectedBox = nullptr;

	m_prevSelectedPosX = 0, m_prevSelectedPosY = 0;
	m_curSelectedPosX = 0, m_curSelectedPosY = 0;
	m_mouseSelectedPosMinInterval = 500;
	m_rectMinInterval = 100;

	m_mouseSelectState = MouseSelectState::DrawBox;
}

CGyunityView::~CGyunityView()
{
}

BOOL CGyunityView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CGyunityView 그리기

void CGyunityView::OnDraw(CDC* pDC)
{
	/*CGyunityDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;*/

	// RenderTarget을 Document에 저장. 매번 저장하고있어서 효율이 떨어질지도..
	CGyunityDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	pDoc->m_rt = m_pRenderTarget;
	// 이것도 효율이..
	pDoc->m_mainView = this;


	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Pink));
	if (pDoc->m_dataControl->m_sprites.find(L"test") != pDoc->m_dataControl->m_sprites.end())
	{
		Sprite* spr = pDoc->m_dataControl->m_sprites[L"test"];
		CD2DSizeF size = spr->m_d2dBitmap->GetSize();
		CD2DRectF rectangle(0.0f, 0.0f, size.width, size.height);
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
		m_pRenderTarget->DrawBitmap(spr->m_d2dBitmap, &rectangle);
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	m_pRenderTarget->DrawRectangle({ m_rectX,m_rectY,m_rectCx,m_rectCy }, m_pGreenBrush);
	
	for (const auto& extractBox: GetDocument()->m_dataControl->m_extractedSprites)
	{
		extractBox->Render(m_pRenderTarget);
		//Invalidate();
	}


	m_pRenderTarget->EndDraw();
}


// CGyunityView 인쇄

BOOL CGyunityView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGyunityView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGyunityView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGyunityView 진단

#ifdef _DEBUG
void CGyunityView::AssertValid() const
{
	CView::AssertValid();
}

void CGyunityView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


#endif //_DEBUG


void CGyunityView::OnNewImage()
{

	//LPCTSTR ll = {_T("비트맵파일(*.bmp)|*.bmp|모든파일|*.*||")};
	LPCTSTR ll = { _T("Image Files(*.bmp;*.png;*.jpg;*.jepg||") };
	CFileDialog dlg(TRUE, _T(".bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ll);
	if (dlg.DoModal() == IDOK)
	{
		GetDocument();
		CString tempFileName;
		dlg.GetPathName();
		//tempFileName = dlg.GetFileName();
		tempFileName = dlg.GetPathName();

		LoadBitMapByFilePath(tempFileName);
		// 파일 경로를 알았으니 파일을 불러와야 함.
	}
}


void CGyunityView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
}



void CGyunityView::MyInitialize()
{
	// Enable D2D support for this window
	EnableD2DSupport();


	// Init D2D resources
	m_pBlackBrush = new CD2DSolidColorBrush(
		GetRenderTarget(),
		D2D1::ColorF(D2D1::ColorF::Black)
	);

	m_pGreenBrush = new CD2DSolidColorBrush(GetRenderTarget(), D2D1::ColorF(D2D1::ColorF::Green));

	m_pTextFormat = new CD2DTextFormat(
		GetRenderTarget(),
		_T("Verdana"),
		50
	);

	m_pTextFormat->Get()->SetTextAlignment(
		DWRITE_TEXT_ALIGNMENT_CENTER
	);

	m_pTextFormat->Get()->SetParagraphAlignment(
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER
	);
}

void CGyunityView::LoadBitMapByFilePath(const LPCTSTR& filePath, HINSTANCE hInst /*= nullptr*/)
{
	HINSTANCE hResInstance = AfxGetResourceHandle();

	Sprite* sprite = new Sprite();
	sprite->m_d2dBitmap = new CD2DBitmap(m_pRenderTarget, filePath, CD2DSizeU(0, 0), TRUE);

	sprite->m_d2dBitmap->Create(m_pRenderTarget);

	AfxSetResourceHandle(hResInstance);

	CD2DSizeF size = sprite->m_d2dBitmap->GetSize();
	CD2DRectF rectangle(0.0f, 0.0f, size.width, size.height);
	m_sprites.insert({ L"test", sprite });
	Invalidate();
}

CGyunityDoc* CGyunityView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{

#ifndef _DEBUG  // GyunityView.cpp의 디버그 버전
	 //inline CGyunityDoc* CGyunityView::GetDocument() const
	    { return reinterpret_cast<CGyunityDoc*>(m_pDocument); }
#endif

// 	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGyunityDoc)));
// 	return (CGyunityDoc*)m_pDocument;
// 
	//ASSERT_VALID(this);
	CRuntimeClass* cl = m_pDocument->GetRuntimeClass();
	//AfxMessageBox(CString(cl->m_lpszClassName));
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGyunityDoc)));
	return (CGyunityDoc*)m_pDocument;
}


void CGyunityView::OnAnimationPlay()
{

}


void CGyunityView::OnAnimationReverseplay()
{

}


void CGyunityView::OnAnimationStop()
{
	
		
}

void CGyunityView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_isClicked)
	{
		m_isClicked = true;

		// shift가 안 눌려있을 경우 queue를 초기화 함.
		if (m_shiftDown == false)
		{
			ClearSelectedBox();
			//Invalidate(TRUE);
		}

		// 이미 선택되어 있을 경우 Selected 를 false로 바꾸어줌
		if (m_selectedBox != nullptr)
		{
			// 처음 shift를 눌렀을 경우 이전 박스와 현재 박스 모두 queue에 넣어주어야 한다.
			// 이 코드는 이전 박스만 넣어준다.
			if (m_selectedCount == 0 && m_shiftDown == true)
			{
				PushSelectedBox(m_selectedBox);
			}

			// 다중 선택 옵션이 아닐 경우 상자의 selected를 꺼준다.
			if(m_shiftDown == false)
				m_selectedBox->Selected = false;
		}
		m_selectedBox = nullptr;
		
		// 마우스의 위치에 상자가 있는지 확인
		ExtractedSprite* rect = IsBoxPosition(point);

		// 상자가 있을 경우 아래의 블록 실행
		if (rect != nullptr)
		{
			m_selectedBox = rect;
			m_selectedBox->Selected = true;

			m_prevSelectedPosX = point.x;
			m_prevSelectedPosY = point.y;
			m_canMoveSmooth = false;

			// 선택된 상자 queue에 추가
			PushSelectedBox(m_selectedBox);

			// 선택된 상자의 정보를 infoView에 출력
			GetDocument()->m_spriteInfoView->GetSpriteInfo(m_selectedBox);

			m_mouseSelectState = MouseSelectState::SelectBox;
			return;
		}

		// 선택되어 있지 않을 경우 DrawBox 모드로 설정
		m_mouseSelectState = MouseSelectState::DrawBox;
		m_rectX = point.x;
		m_rectY = point.y;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CGyunityView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_isClicked)
	{
		switch (m_mouseSelectState)
		{
		case MouseSelectState::DrawBox:
		{

			// 마우스가 왼쪽 대각선 아래, 또는 위로 가게 상자를 그리면 취소시켜버림
			if (point.x < m_rectX || point.y < m_rectY)
			{
				m_rectX = 0;
				m_rectY = 0;
				m_rectCx = 0;
				m_rectCy = 0;
				m_mouseSelectState = MouseSelectState::None;
				break;
			}

			m_rectCx = point.x;
			m_rectCy = point.y;
		}
		break;
		case MouseSelectState::SelectBox:
		{
			if (m_selectedBox == nullptr)
				break;

			// 마우스를 조금만 움직였을 경우 아직 움직이지 않게 하기 위해 여유를 둔다
			m_curSelectedPosX = point.x;
			m_curSelectedPosY = point.y;

			float curToPrevX = m_curSelectedPosX - m_prevSelectedPosX;
			float curToPrevY = m_curSelectedPosY - m_prevSelectedPosY;
			if (m_canMoveSmooth == false && (curToPrevX * curToPrevX) + (curToPrevY * curToPrevY) < m_mouseSelectedPosMinInterval)
			{
				break;
			}
			m_canMoveSmooth = true;

			m_rectX = 0;
			m_rectY = 0;
			m_rectCx = 0;
			m_rectCy = 0;

			float leftToRightSize = abs(m_selectedBox->Right - m_selectedBox->Left);
			float topToBottomSize = abs(m_selectedBox->Bottom - m_selectedBox->Top);

			m_selectedBox->Left = point.x - (leftToRightSize / 2);
			m_selectedBox->Right = point.x + (leftToRightSize / 2);
			m_selectedBox->Top = point.y - (topToBottomSize / 2);
			m_selectedBox->Bottom = point.y + (topToBottomSize / 2);

			// 이거 사용하면 계속 정보를 갱신하지만 프레임 드랍 오짐
			//GetDocument()->m_spriteInfoView->GetSpriteInfo(m_selectedBox);
		}
		break;
		default:
			break;
		}
		Invalidate();
	}
}


void CGyunityView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_isClicked)
	{
		m_isClicked = false;
		m_rectCx = point.x;
		m_rectCy = point.y;

		switch (m_mouseSelectState)
		{
		case MouseSelectState::None:
		{

		}
			break;
		case MouseSelectState::DrawBox:
		{
			// 마우스를 조금만 움직였을 경우 상자를 만들지 않는다.
			m_curSelectedPosX = point.x;
			m_curSelectedPosY = point.y;

			float curToPrevX = m_rectCx - m_rectX;
			float curToPrevY = m_rectCy - m_rectY;
			if ((curToPrevX * curToPrevX) + (curToPrevY * curToPrevY) < m_rectMinInterval)
			{
				break;
			}

			//ExtractedSprite* slice = new ExtractedSprite( m_rectX , m_rectY , m_rectCx, m_rectCy, m_rectX + (m_rectCx - m_rectX)/ 2, m_rectY + (m_rectCy - m_rectY) / 2 );
			ExtractedSprite* slice = new ExtractedSprite(m_rectX, m_rectY, m_rectCx, m_rectCy, 0.5f, 0.5f);
			GetDocument()->m_dataControl->m_extractedSprites.push_back(slice);
		}
		break;
		case MouseSelectState::SelectBox:
		{
			m_rectX = 0;
			m_rectY = 0;
			m_rectCx = 0;
			m_rectCy = 0;
			//m_selectedBox = nullptr;
			
			// 선택된 상자의 정보를 infoView에 갱신해서 출력
			GetDocument()->m_spriteInfoView->GetSpriteInfo(m_selectedBox);
		}
			break;
		default:
			break;
		}
	}
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


ExtractedSprite* CGyunityView::IsBoxPosition(CPoint point)
{
	// 거꾸로 순회 : 마지막에 그린(가장 최근에 그린) 상자를 선택할 수 있게

	for (auto it = GetDocument()->m_dataControl->m_extractedSprites.rbegin(); it != GetDocument()->m_dataControl->m_extractedSprites.rend(); ++it)
	{
		auto c = *it;

		int x = point.x, y = point.y;
		if (x < c->Left) continue;
		if (x > c->Right) continue;

		// 아래로갈수록 y값이 커짐
		if (y > c->Bottom) continue;
		if (y < c->Top) continue;
		return c;
	}
	return nullptr;
}

void CGyunityView::AutoSlice(const SlicePivotInfo& pivotInfo, float costumeX /*= 0*/, float costumeY /*= 0*/)
{

	if (GetDocument()->m_dataControl->m_mainSprite == nullptr)
	{
		MessageBox(_T("메인 이미지가 없습니다."));
		return;
	}
	HWND hwnd = GetRenderTarget()->GetHwnd();
	HDC hdc = ::GetDC(hwnd);

	HDC hMemoryDC = CreateCompatibleDC(hdc);
	//COLORREF color = GetPixel(hdc, 0, 0);


	// temp 임시 용 변수 :: 이 색은 신경 안쓸 것
	COLORREF keyColor = RGB(255, 255, 255);

	CD2DSizeF size = GetDocument()->m_dataControl->m_mainSprite->m_d2dBitmap->GetSize();
	
	m_visitedPixel = std::vector<std::vector<bool>>(size.height,(std::vector<bool>(size.width, false)));
	//m_visitedPixel = std::vector<std::vector<bool>>(700,(std::vector<bool>(700, false)));
	m_width = size.width;
	m_height = size.height;

	keyColor = GetPixel(hdc, 0, 0);


	for (int y = 0; y < size.height; y+=10)
	{
		for (int x = 0; x < size.width; x+=10)
		{
			if(m_visitedPixel[y][x] == true)
				continue;


			COLORREF color = GetPixel(hdc, x, y);
			if (color == keyColor) continue;

			int a = 3;
			m_thisMaxLeft = x;
			m_thisMaxRight = x;
			m_thisMaxTop = y;
			m_thisMaxBottom = y;

			/// 여기서 bfs 돌려야 함.
			//DFSForAutoSlice(x, y, keyColor, hdc);
			BFSForAutoSlice(x, y, keyColor, hdc);
			
			CD2DPointF pivot = GetPivotByInfo(pivotInfo, { m_thisMaxLeft, m_thisMaxTop, m_thisMaxRight, m_thisMaxBottom }, costumeX, costumeY);
			ExtractedSprite* sliceSprite = new ExtractedSprite(m_thisMaxLeft, m_thisMaxTop, m_thisMaxRight, m_thisMaxBottom, pivot.x, pivot.y);
			sliceSprite->Name = MakeSpriteName();
			GetDocument()->m_dataControl->m_extractedSprites.push_back(sliceSprite);
		}
	}
	Invalidate();
}

void CGyunityView::GridByCellSize(const SlicePivotInfo& pivotInfo, float x, float y, float costumeX /*= 0*/, float costumeY /*= 0*/)
{
	if (GetDocument()->m_dataControl->m_mainSprite == nullptr)
	{
		MessageBox(_T("메인 이미지가 없습니다."));
		return;
	}
	// Grid by cell size
	CD2DSizeF size = GetDocument()->m_dataControl->m_mainSprite->m_d2dBitmap->GetSize();
	float boxPositionToDrawX = 0;
	float boxPositionToDrawY = 0;

	int c = 0, r = 0;
	c = size.width / x;
	r = size.height / y;

	int count = c * r;
	for (int i = 0; i < count; i++)
	{
		CD2DPointF pivot = GetPivotByInfo(pivotInfo, { boxPositionToDrawX, boxPositionToDrawY, boxPositionToDrawX + x,
			boxPositionToDrawY + y }, costumeX, costumeY);
		ExtractedSprite* box = new ExtractedSprite(
			boxPositionToDrawX,
			boxPositionToDrawY,
			boxPositionToDrawX + x,
			boxPositionToDrawY + y,
			pivot.x,
			pivot.y
		);
		box->Name = MakeSpriteName();
		GetDocument()->m_dataControl->m_extractedSprites.push_back(box);
		boxPositionToDrawX = ((i + 1) % c) * x;
		boxPositionToDrawY = ((i + 1) / c) * y;
	}
	Invalidate();
}

void CGyunityView::GridByCellCount(const SlicePivotInfo& pivotInfo, int c, int r, float coustomX /*= 0*/, float coustomY /*= 0*/)
{
	if (GetDocument()->m_dataControl->m_mainSprite == nullptr)
	{
		MessageBox(_T("메인 이미지가 없습니다."));
		return;
	}
	// Grid by cell count
	CD2DSizeF size = GetDocument()->m_dataControl->m_mainSprite->m_d2dBitmap->GetSize();
	CD2DRectF rectangle(0.0f, 0.0f, size.width, size.height);

	float boxWidth = size.width / c;
	float boxHeight = size.height / r;

	float boxPositionToDrawX = 0;
	float boxPositionToDrawY = 0;
	int count = c * r;
	for (int i = 0; i < count; i++)
	{
		CD2DPointF pivot = GetPivotByInfo(pivotInfo, { boxPositionToDrawX, boxPositionToDrawY, boxPositionToDrawX + boxWidth,
			boxPositionToDrawY + boxHeight }, coustomX, coustomY);
		ExtractedSprite* box = new ExtractedSprite(
			boxPositionToDrawX,
			boxPositionToDrawY,
			boxPositionToDrawX + boxWidth,
			boxPositionToDrawY + boxHeight,
			pivot.x,
			pivot.y
		);
		box->Name = MakeSpriteName();
		GetDocument()->m_dataControl->m_extractedSprites.push_back(box);
		boxPositionToDrawX = ((i + 1) % c) * boxWidth;
		boxPositionToDrawY = ((i + 1) / c) * boxHeight;
	}
	Invalidate();
}


void CGyunityView::AutoSliceV2()
{
	if (GetDocument()->m_dataControl->m_mainSprite == nullptr)
	{
		MessageBox(_T("메인 이미지가 없습니다."));
		return;
	}

	GetDocument()->m_dataControl->m_mainSprite->ExtractPixelData();


	HWND hwnd = GetRenderTarget()->GetHwnd();
	HDC hdc = ::GetDC(hwnd);

	HDC hMemoryDC = CreateCompatibleDC(hdc);
	//COLORREF color = GetPixel(hdc, 0, 0);


	// temp 임시 용 변수 :: 이 색은 신경 안쓸 것
	COLORREF keyColor = RGB(255, 255, 255);

	CD2DSizeF size = GetDocument()->m_dataControl->m_mainSprite->m_d2dBitmap->GetSize();

	//m_visitedPixel = std::vector<std::vector<bool>>(size.height, (std::vector<bool>(size.width, false)));
	m_width = size.width;
	m_height = size.height;

	keyColor = GetPixel(hdc, 0, 0);

	std::vector<CD2DRectU> ExtractedRects;
	Sprite::ExtractRectsFromSprites(hdc, GetDocument()->m_dataControl->m_mainSprite, keyColor, ExtractedRects);

	int a = 3;
}

CD2DPointF CGyunityView::GetPivotByInfo(const SlicePivotInfo& pivotInfo, const CD2DRectF& rect, float costumeX /*= 0*/, float costumeY /*= 0*/)
{
	CD2DPointF returnPivot = { 0,0 };
	switch (pivotInfo)
	{
	case Center:
	{
		//returnPivot.x = rect.left + (rect.right - rect.left)/ 2;
		//returnPivot.y = rect.top + (rect.bottom - rect.top) / 2;

		returnPivot.x = 0.5f;
		returnPivot.y = 0.5f;
	}
		break;
	case TopLeft:
	{
		returnPivot.x = 0.f;
		returnPivot.y = 0.f;
	}
		break;
	case Top:
	{
		returnPivot.x = 0.5f;
		returnPivot.y = 0.f;
	}
		break;
	case TopRight:
	{
		returnPivot.x = 1.f;
		returnPivot.y = 0.f;
	}
		break;
	case Left:
	{
		returnPivot.x = 0.f;
		returnPivot.y = 0.5f;
	}
		break;
	case Right:
	{
		returnPivot.x = 1.f;
		returnPivot.y = 0.5f;
	}
		break;
	case BottomLeft:
	{
		returnPivot.x = 0.f;
		returnPivot.y = 1.f;
	}
		break;
	case Bottom:
	{
		returnPivot.x = 0.5f;
		returnPivot.y = 1.f;
	}
		break;
	case BottomRight:
	{
		returnPivot.x = 1.f;
		returnPivot.y = 1.f;
	}
		break;
	case Custom:
	{
		// coustom pivot은 비율에 따라 결정
		//returnPivot.x = rect.left + (rect.right - rect.left) * costumeX;
		//returnPivot.y = rect.bottom + (rect.top - rect.bottom) * costumeY;

		returnPivot.x = costumeX;
		returnPivot.y = costumeY;
	}
		break;
	default:
		break;
	}
	return returnPivot;
}

void CGyunityView::DFSForAutoSlice(int& x, int& y, COLORREF& color, HDC& hdc)
{

	//// Stack overflow

	m_visitedPixel[y][x] = true;

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		COLORREF thisColor = GetPixel(hdc, x, y);
		if (nx < 0 || ny < 0 || nx > m_width - 1 || ny > m_height - 1) continue;
		if (color == thisColor)
			continue;
		if (m_visitedPixel[ny][nx] == true) continue;
		if (nx < m_thisMaxLeft) m_thisMaxLeft = nx;
		if (nx > m_thisMaxRight) m_thisMaxRight = nx;
		if (ny < m_thisMaxTop) m_thisMaxTop = ny;
		if (ny > m_thisMaxBottom) m_thisMaxBottom = ny;

		DFSForAutoSlice(nx, ny, color, hdc);
	}
	return;
}

void CGyunityView::BFSForAutoSlice(int& x, int& y, COLORREF& keyColor, HDC& hdc)
{
	m_visitedPixel[y][x] = true;
	std::queue<std::pair<int, int>> q;
	q.push({ y,x });
	while (!q.empty())
	{
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			COLORREF thisColor = GetPixel(hdc, nx, ny);
			if (nx < 0 || ny < 0 || nx > m_width - 1 || ny > m_height - 1) continue;
			if (keyColor == thisColor)
				continue;
			if (m_visitedPixel[ny][nx] == true) continue;
 
//   			bool isBoundary = true;
//   			for (int j = 0; j < 4; j++)
//   			{
//   				int nny = ny + dy[i];
//   				int nnx = nx + dx[i];
//   				if (nny == cy && nnx == cx) continue;
//   				if (nx < 0 || ny < 0 || nx > m_width - 1 || ny > m_height - 1) continue;
//   				COLORREF nextColor = GetPixel(hdc, nnx, nny);
//   				if (nextColor == keyColor)
//   				{
//   					isBoundary = true;
//   				}
//   			}
//   			if (!isBoundary) continue;

			if (nx < m_thisMaxLeft) m_thisMaxLeft = nx;
			if (nx > m_thisMaxRight) m_thisMaxRight = nx;
			if (ny < m_thisMaxTop) m_thisMaxTop = ny;
			if (ny > m_thisMaxBottom) m_thisMaxBottom = ny;
			m_visitedPixel[ny][nx] = true;
			q.push({ ny,nx });
		}
	}
	for (int i = m_thisMaxTop; i < m_thisMaxBottom; i++)
	{
		for (int j = m_thisMaxLeft; j < m_thisMaxRight; j++)
		{
			m_visitedPixel[i][j] = true;
		}
	}
}

std::wstring CGyunityView::MakeSpriteName()
{
	std::wstring ret = GetDocument()->m_dataControl->m_mainSpriteName;
	std::wstring idx = std::to_wstring(m_spriteNameIndex);
	ret += '_';
	ret += idx;
	m_spriteNameIndex++;
	return ret;
}

void CGyunityView::PushSelectedBox(ExtractedSprite* box)
{
	// 처음 다중 선택할 경우 이전에 선택되어 있던 0번째부터 큐에 추가 후 지금 선택한 상자를 큐에 추가
	//if(m_selectedCount == 0)
	//	m_selectedBoxQueue.push(m_selectedBox);
	// 근데 위에 거를 다른데서 해야할 듯

	GetDocument()->m_dataControl->m_selectedBoxQueue.push(box);
	m_selectedCount++;
}

void CGyunityView::ClearSelectedBox()
{
	while (!GetDocument()->m_dataControl->m_selectedBoxQueue.empty())
	{
		GetDocument()->m_dataControl->m_selectedBoxQueue.front()->Selected = false;
		GetDocument()->m_dataControl->m_selectedBoxQueue.pop();
	}



	//m_selectedBoxQueue = std::queue<ExtractedSprite*>();
}

void CGyunityView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_SHIFT)
	{
		m_shiftDown = true;
	}

	if (nChar == VK_DELETE)
	{
		// 선택된 slice sprite 지우기
		if (m_selectedBox != nullptr)
		{
			auto it = std::find(GetDocument()->m_dataControl->m_extractedSprites.begin(), GetDocument()->m_dataControl->m_extractedSprites.end(), m_selectedBox);

			if (it != GetDocument()->m_dataControl->m_extractedSprites.end())
			{
				GetDocument()->m_dataControl->m_extractedSprites.erase(it);
			}
			m_selectedBox = nullptr;
			Invalidate();
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CGyunityView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_SHIFT)
	{
		m_shiftDown = false;
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
