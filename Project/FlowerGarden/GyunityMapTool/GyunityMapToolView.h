
// GyunityMapToolView.h: CGyunityMapToolView 클래스의 인터페이스
//

#pragma once


enum class GridType
{
	Ground,
	Map,
	NPC,
};
enum class TileType
{
	World,
	NPC,
};

class Tile;
class TileBrush;
class Grid;
class NPCGrid;
class CGyunityMapToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGyunityMapToolView() noexcept;
	DECLARE_DYNCREATE(CGyunityMapToolView)

		// 특성입니다.
public:
	CGyunityMapToolDoc* GetDocument() const;


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
	virtual ~CGyunityMapToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// my code
public:
	GridType GetGridType() const { return m_gridType; }
	void SetGridType(GridType val) { m_gridType = val; }

	TileType GetTileType() const { return m_tileType; }
	void SetTileType(TileType val) { m_tileType = val; }

	// bitmap불러오기
	CD2DBitmap* LoadBitmapByFilePath(CString filePath);

	// 바닥 그리드
	Grid* m_groundGrid = nullptr;
	// 맵 그리드
	Grid* m_mapGrid = nullptr;
	// Npc 그리드
	NPCGrid* m_npcGrid = nullptr;

	// 그리드를 그리는 브러쉬
	CD2DSolidColorBrush* m_gridBrush;

	COLORREF GetPixelColorFromBitmap(CBitmap* bitmap, int x, int y);
	CBitmap* m_bitmap;

	// 현재 타일브러쉬의 타일 설정
	void SetCurrentTile(Tile* tile);
	TileBrush* GetTileBrush() { return m_tileBrush; }

	int GetTileIndex() const { return m_tileIndex; }
	void SetTileIndex(int val) { m_tileIndex = val; }

	void SetOnGround(bool val) { m_OnGround = val; }
	void SetOnMap(bool val) { m_OnMap = val; }
	void SetOnNPCLayer(bool val) { m_OnNPCLayer = val; }
private:
	// d2d를 초기화합니다.
	void D2DInitialize();

	// 내가 만든 코드들의 초기화
	void Initialize();

	//

	// 스케일 조정
	void SetScreenScale(INT parameter, CPoint mousePos);
	float m_gridScale = 1.f;
	float m_currentPos = 0.f;

	// Tile만들기

	// 타일을 그리는 타일 브러쉬
	TileBrush* m_tileBrush;
	int m_tileIndex = -1;

	void DrawGroundGrid();
	void DrawMapGrid();
	void DrawNPCLayerGrid();

	GridType m_gridType = GridType::Ground;
	TileType m_tileType = TileType::World;
	// 마우스 왼쪽 클릭
	bool m_isLMouseClicked = false;

	// 마우스 우클릭
	bool m_isRMouseClicked = false;
	CPoint m_prevMousePos = {};

	// ground 또는 NpcLayer, map이 보이게 할 지 정하는 변수
	bool m_OnGround = true;
	bool m_OnNPCLayer = true;
	bool m_OnMap = true;

	// end my code

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEditUndo();
	afx_msg void OnRedo();
	virtual void OnInitialUpdate();
};

// #ifndef _DEBUG  // GyunityMapToolView.cpp의 디버그 버전
// inline CGyunityMapToolDoc* CGyunityMapToolView::GetDocument() const
//    { return reinterpret_cast<CGyunityMapToolDoc*>(m_pDocument); }
// #endif

