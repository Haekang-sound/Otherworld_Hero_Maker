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
	/// ���� ���带 �ٲߴϴ�.
	/// ������, �����͸� �ٲߴϴ�..
	/// </summary>
	/// <param name="world"></param>
	void SetCurrentWorld(MyMap* world);
	bool GetGridOn() const { return m_GridOn; }
	void SetGridOn(bool val) { m_GridOn = val; }
private:

	// ���� ��
	MyMap* currentWorld = nullptr;

	Vector2 vWorldSize = { 14, 10 };
	Vector2 vTileSize = { 144, 72 };

	// ����� ��ġ (���� �𸣰����� �Ƹ� x���� 
	// ������ �������� Ÿ���� ����� �������Ƿ�
	// �׳� ������ ���� �����ϰ� ��, ���������� �� �о���)
	// Vector2 vOrigin = { 5,1 };
	Vector2 vOrigin = { 30,1 };

	int* pWorld = nullptr;
	
	// �����ȣ, ��� �ε���
	std::vector<std::vector<NpcWorldData>> m_NPCPathWorld;

	COLORREF GetPixelColorFromBitmap(CBitmap* bitmap, int x, int y);
	CBitmap* m_mouseOffsetBitmap;

	bool m_GridOn = true;

public:
	void SetMousePoint(CPoint point) { m_mousePoint = point; }
	CPoint m_mousePoint;
	CD2DSolidColorBrush* m_gridBrush;
	TileBrush* m_tileBrush;

	// ���콺�� Ŭ���� ��������
	bool m_mouseClicked = false;
	int m_tileIndex = 0;

	/// <summary>
	/// ���콺�� Ŭ���� ���� ������ �ε����� Ÿ���� ���ϴ�
	/// </summary>
	/// <param name="idx"></param>
	void SetTilePosByMouseClicked(int idx);

	void ResetMouseClicked();

	// Ÿ���� �߰��մϴ�.
	void AddTile(Tile* tile) { m_tiles.push_back(tile); }

	// �ڷΰ���
	void UnDo();
private:
	// �⺻ �ٴ� Ÿ��
	Tile* m_baseTile = nullptr;

	std::vector<Tile*> m_tiles;

	// �ڷΰ���� ������
	//std::stack<std::pair<Vector2,std::pair<int,int>>> m_tilePosStack;
	std::stack<UnDoData> m_tilePosStack;
};

