#pragma once
#include "MyMap.h"
class Tile;
class TileBrush;
//class MyMap;

struct UnDoData
{
	Vector2 beforePos;
	int beforeNpcIndex;
	int beforeNpcPathCount;
	//std::pair<int, int> beforeNpcWorldData;
	NpcWorldData beforeNpcWorldData;
};

class NPCGrid
{
public:
	NPCGrid();
	~NPCGrid();
	void Initialize(TileBrush* tilebrush);
	void Update();
	void Render(CRenderTarget* renderTarget);

	Tile* GetBaseTile() const { return m_baseTile; }
	void SetBaseTile(Tile* val) { m_baseTile = val; }

	/// <summary>
	/// 현재 월드를 바꿉니다.
	/// 사이즈, 데이터를 바꿉니다..
	/// </summary>
	/// <param name="world"></param>
	void SetCurrentWorld(MyMap* world);
	bool GetGridOn() const { return m_GridOn; }
	void SetGridOn(bool val) { m_GridOn = val; }
private:

	// 현재 맵
	MyMap* currentWorld = nullptr;

	Vector2 vWorldSize = { 14, 10 };
	Vector2 vTileSize = { 144, 72 };

	// 출발할 위치 (왠진 모르겠지만 아마 x값이 
	// 음수로 떨어지면 타일이 제대로 안찍히므로
	// 그냥 오른쪽 부터 시작하게 함, 오른쪽으로 쭉 밀어줌)
	// Vector2 vOrigin = { 5,1 };
	Vector2 vOrigin = { 30,1 };

	int* pWorld = nullptr;
	
	// 사람번호, 경로 인덱스
	std::vector<std::vector<NpcWorldData>> m_NPCPathWorld;

	COLORREF GetPixelColorFromBitmap(CBitmap* bitmap, int x, int y);
	CBitmap* m_mouseOffsetBitmap;

	bool m_GridOn = true;

public:
	void SetMousePoint(CPoint point) { m_mousePoint = point; }
	CPoint m_mousePoint;
	CD2DSolidColorBrush* m_gridBrush;
	TileBrush* m_tileBrush;

	// 마우스가 클릭된 상태인지
	bool m_mouseClicked = false;
	int m_tileIndex = 0;

	/// <summary>
	/// 마우스를 클릭한 곳에 지정된 인덱스의 타일을 깝니다
	/// </summary>
	/// <param name="idx"></param>
	void SetTilePosByMouseClicked(int idx);

	void ResetMouseClicked();

	// 타일을 추가합니다.
	void AddTile(Tile* tile) { m_tiles.push_back(tile); }

	// 뒤로가기
	void UnDo();
private:
	// 기본 바닥 타일
	Tile* m_baseTile = nullptr;

	std::vector<Tile*> m_tiles;

	// 뒤로가기용 변수들
	//std::stack<std::pair<Vector2,std::pair<int,int>>> m_tilePosStack;
	std::stack<UnDoData> m_tilePosStack;
};

