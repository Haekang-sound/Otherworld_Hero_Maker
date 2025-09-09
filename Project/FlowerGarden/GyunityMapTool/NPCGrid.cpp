#include "pch.h"
#include "NPCGrid.h"
#include "Tile.h"
#include "resource.h"
#include "TileBrush.h"
#include "MyMap.h"
#include "Global.h"

NPCGrid::NPCGrid()
{

}

NPCGrid::~NPCGrid()
{

}

void NPCGrid::Initialize(TileBrush* tilebrush)
{
	pWorld = new int[vWorldSize.x * vWorldSize.y] {-1, };
	::memset(pWorld, -1, sizeof(int) * vWorldSize.x * vWorldSize.y);

	/*pNPCPathWorld = std::vector<std::vector<std::pair<int, int>>>(vWorldSize.y, std::vector<std::pair<int, int>>(vWorldSize.x));
	for (int y = 0; y < vWorldSize.y; y++)
	{
		for (int x = 0; x < vWorldSize.x; x++)
		{
			pNPCPathWorld[y][x].first = -1;
			pNPCPathWorld[y][x].second = -1;
		}
	}*/
	//m_gridBrush = brush;
	m_tileBrush = tilebrush;

	m_mouseOffsetBitmap = new CBitmap();
	HRESULT hr = m_mouseOffsetBitmap->LoadBitmap(IDB_POS_BMP);
}

void NPCGrid::Update()
{

}

void NPCGrid::Render(CRenderTarget* renderTarget)
{
	if (m_baseTile == nullptr) return;
	if (currentWorld == nullptr) return;

	//Vector2 vMouse = { m_mousePoint.x, m_mousePoint.y };
	// 카메라 위치 반영버전으로 바꿈.
	Vector2 vMouse = { m_mousePoint.x - g_CameraPos.dx, m_mousePoint.y - g_CameraPos.dy };
	Vector2 vCell = { vMouse.x / vTileSize.x, vMouse.y / vTileSize.y };
	Vector2 vOffset = { vMouse.x % vTileSize.x, vMouse.y % vTileSize.y };
	COLORREF col = GetPixelColorFromBitmap(m_mouseOffsetBitmap,/* 3 * vTileSize.x + */vOffset.x, vOffset.y);

	Vector2 vSelected =
	{
		(vCell.y - vOrigin.y) + (vCell.x - vOrigin.x),
		(vCell.y - vOrigin.y) - (vCell.x - vOrigin.x)
	};


	if (col == RGB(255, 0, 0)) { vSelected.x += -1; }	// r
	if (col == RGB(0, 255, 0)) { vSelected.y += 1; }	// g
	if (col == RGB(0, 0, 255)) { vSelected.y += -1; }	// b
	if (col == RGB(255, 255, 0)) { vSelected.x += 1; }	// yellow


	auto ToScreen = [&](int x, int y)
	{
		return Vector2
		{
		(vOrigin.x * vTileSize.x) + (x - y) * (vTileSize.x / 2),
		(vOrigin.y * vTileSize.y) + (x + y) * (vTileSize.y / 2)
		};
	};

	std::vector<std::vector<NpcWorldData>>& npcPathWorld = currentWorld->GetNpcWorldData();

	if (m_mouseClicked)	// mouse clicked
	{
		if (vSelected.x >= 0 && vSelected.x < vWorldSize.x && vSelected.y >= 0 && vSelected.y < vWorldSize.y)
		{
			pWorld[vSelected.y * vWorldSize.x + vSelected.x] = m_tileIndex;	// 이 위치의 타일을 바꿀 것.

			// 아래는 NPC 경로 체크
			if (npcPathWorld[vSelected.y][vSelected.x].npcIdx == m_tileIndex)
			{
				// 이미 칠해져있는 경우 갱신해주지 않음.
			}
			else
			{
				// 아래는 해당 NPC의 경로가 몇개인지 받아옴.
				int currentNpcPathCount = 0;
				for (int cy = 0; cy < vWorldSize.y; cy++)
				{
					for (int cx = 0; cx < vWorldSize.x; cx++)
					{
						if (m_tileIndex == npcPathWorld[cy][cx].npcIdx)
						{
							currentNpcPathCount = max(currentNpcPathCount, npcPathWorld[cy][cx].npcPathCount);
						}
					}
				}
				UnDoData unDoData;
				unDoData.beforePos = vSelected;
				unDoData.beforeNpcWorldData = npcPathWorld[vSelected.y][vSelected.x];
				unDoData.beforeNpcIndex = npcPathWorld[vSelected.y][vSelected.x].npcIdx;
				unDoData.beforeNpcPathCount = npcPathWorld[vSelected.y][vSelected.x].npcPathCount;
				// test
				m_tilePosStack.push(unDoData);
				//m_tilePosStack.push({ vSelected, {pNPCPathWorld[vSelected.y][vSelected.x].first,pNPCPathWorld[vSelected.y][vSelected.x].second } });

				npcPathWorld[vSelected.y][vSelected.x].npcIdx = m_tileIndex;
				npcPathWorld[vSelected.y][vSelected.x].npcPathCount = currentNpcPathCount + 1;
				npcPathWorld[vSelected.y][vSelected.x].npcId = m_tiles[m_tileIndex]->GetNpcID();
			}
		}
	}
	// 	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	// 	renderTarget->SetTransform(D2D1::Matrix3x2F::Scale(g_Scale, g_Scale));
	Vector2 renderPos = { 0,0 };
	int prevY = 0;
	int prevX = 0;
	while (true)
	{
		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		// Render
		Vector2 vWorld = ToScreen(renderPos.x, renderPos.y);

		int idx = renderPos.y * vWorldSize.x + renderPos.x;

		switch (pWorld[idx])	// tile 종류
		{
			case -1:
				if (GetGridOn() == false) break;
				// Invisible Tile
				GetBaseTile()->Pos = vWorld;
				GetBaseTile()->Render(renderTarget);
				break;

			default:
				Vector2 StartPos = { 0,0 };
				StartPos.x = vWorld.x;
				//StartPos.y = vWorld.y - (m_tiles[pWorld[idx]]->GetSize().height - vTileSize.y);
				vWorld.y += 72;
				StartPos.y = vWorld.y - m_tiles[pWorld[idx]]->GetSize().height;

				int heightValue = m_tiles[pWorld[idx]]->GetSize().height;

				int v = heightValue / 72;
				if (v % 2 == 0)
					StartPos.y += 36;


				// 파일의 첫 글자가 U면 아래로 36 (y += 36)
				// 파일의 첫 글자가 D면 위로 36 (y -= 36)

				if (m_tiles[pWorld[idx]]->GetName()[0] == 'U')
				{
					StartPos.y += 36;
				}
				if (m_tiles[pWorld[idx]]->GetName()[0] == 'D')
				{
					StartPos.y -= 36;
				}

				m_tiles[pWorld[idx]]->Pos = StartPos;
				m_tiles[pWorld[idx]]->Render(renderTarget);
				break;
		}

		if (renderPos.x == vWorldSize.x - 1 && renderPos.y == vWorldSize.y - 1)
		{
			break;
		}

		if (renderPos.x == vWorldSize.x - 1)
		{
			prevX++;
			renderPos.x = prevX;
			renderPos.y = prevY;
		}
		else if (renderPos.y == 0)
		{
			prevY++;
			renderPos.y = prevY;
			renderPos.x = 0;
		}
		else
		{
			renderPos.y -= 1;
			renderPos.x += 1;
		}

		if (renderPos.y > vWorldSize.y - 1)
			renderPos.y--;
		if (renderPos.x > vWorldSize.x - 1)
			renderPos.x--;
	}




	//Vector2 vSelectedWorld = ToScreen(vSelected.x, vSelected.y);
	Vector2 vSelectedWorld = ToScreen(vSelected.x, vSelected.y);
	if (m_tileBrush == nullptr)
	{
		// 	renderTarget->DrawRectangle(
		// 		CD2DRectF(vCell.x * vTileSize.x,
		// 			vCell.y * vTileSize.y,
		// 			vCell.x * vTileSize.x + vTileSize.x,
		// 			vCell.y * vTileSize.y + vTileSize.y
		// 		)
		// 		m_gridBrush);
	}
	else
	{
		if (m_tileBrush->GetTile() != nullptr)
		{
			Vector2 StartPos = { 0,0 };
			StartPos.x = vSelectedWorld.x;
			StartPos.y = vSelectedWorld.y - (m_tileBrush->GetTile()->GetSize().height - vTileSize.y);

			int heightValue = m_tileBrush->GetTile()->GetSize().height;
			int v = heightValue / 72;
			if (v % 2 == 0)
				StartPos.y += 36;

			// 			float heightValue = (m_tileBrush->GetTile()->GetSize().height - 72) / 36;
						//StartPos.y = vSelectedWorld.y - (m_tileBrush->GetTile()->GetSize().height - vTileSize.y);

						//m_tileBrush->GetTile()->Pos = vSelectedWorld;
			if (m_tileBrush->GetTile()->GetName()[0] == 'U')
			{
				StartPos.y += 36;
			}
			if (m_tileBrush->GetTile()->GetName()[0] == 'D')
			{
				StartPos.y -= 36;
			}
			m_tileBrush->GetTile()->Pos = StartPos;
			m_tileBrush->GetTile()->Render(renderTarget);
		}
	}

	// 마우스가 클릭되었을 경우 마우스 클릭을 초기화
	ResetMouseClicked();
}

void NPCGrid::SetCurrentWorld(MyMap* world)
{
	currentWorld = world;
	if (world == nullptr) return;
	pWorld = (world->GetWorldData());
	vWorldSize = world->GetWorldSize();
	return;
	m_NPCPathWorld = std::vector<std::vector<NpcWorldData>>(vWorldSize.y, std::vector<NpcWorldData>(vWorldSize.x));
	m_NPCPathWorld = world->GetNpcWorldData();
	
	for (int y = 0; y < vWorldSize.y; y++)
	{
		for (int x = 0; x < vWorldSize.x; x++)
		{
			m_NPCPathWorld[y][x] = world->GetNpcWorldData()[y][x];

			//m_NPCPathWorld[y][x].npcIdx = -1;
			//m_NPCPathWorld[y][x].npcPathCount = -1;
		}
	}
	
}

COLORREF NPCGrid::GetPixelColorFromBitmap(CBitmap* bitmap, int x, int y)
{
	CDC dc;
	dc.CreateCompatibleDC(nullptr);
	CBitmap* oldBitmap = dc.SelectObject(bitmap);
	COLORREF color = dc.GetPixel(x, y);
	int a = GetRValue(color);
	int b = GetGValue(color);
	int c = GetBValue(color);
	dc.SelectObject(oldBitmap);
	dc.DeleteDC();

	return color;
}

void NPCGrid::SetTilePosByMouseClicked(int idx)
{
	m_mouseClicked = true;
	m_tileIndex = idx;
}

void NPCGrid::ResetMouseClicked()
{
	m_mouseClicked = false;
	m_tileIndex = -1;
}

void NPCGrid::UnDo()
{
	if (m_tilePosStack.empty()) return;

	UnDoData undoData = m_tilePosStack.top();
	m_tilePosStack.pop();

	Vector2 pos = undoData.beforePos;
	m_NPCPathWorld = currentWorld->GetNpcWorldData();
	pWorld[pos.y * vWorldSize.x + pos.x] = undoData.beforeNpcIndex;
	m_NPCPathWorld[pos.y][pos.x] = undoData.beforeNpcWorldData;
	//m_NPCPathWorld[pos.y][pos.x].npcPathCount = undoData.beforeNpcWorldData.npcPathCount;
	
	// invalidate
}
