#include "pch.h"
#include "Grid.h"
#include "Tile.h"
#include "resource.h"
#include "TileBrush.h"
#include "MyMap.h"
#include "Global.h"
Grid::Grid()
{

}

Grid::~Grid()
{

}

void Grid::Initialize(TileBrush* tilebrush)
{
	//m_baseTile = tile;
	pWorld = new int[vWorldSize.x * vWorldSize.y] {-1, };
	::memset(pWorld, -1, sizeof(int) * vWorldSize.x * vWorldSize.y);
	//m_gridBrush = brush;
	m_tileBrush = tilebrush;

	m_mouseOffsetBitmap = new CBitmap();
	HRESULT hr = m_mouseOffsetBitmap->LoadBitmap(IDB_POS_BMP);

	//TCHAR offsetImagePath[_MAX_PATH];
	//GetCurrentDirectory(_MAX_PATH, offsetImagePath);

	//int cnt = 0;
	//while (offsetImagePath[cnt] != '\0')
	//{
	//	cnt++;
	//}
	//while (offsetImagePath[cnt] != '\\')
	//{
	//	//offsetImagePath[cnt] = '\0';
	//	cnt--;
	//}
	//cnt++;
	////cnt++;
	////offsetImagePath[cnt + 1] = '\0';
	//std::string addPath("GunityMapTool\\resource\\pos.png");
	//for (int i = 0; i < addPath.size(); i++)
	//{
	//	offsetImagePath[cnt] = addPath[i];
	//	cnt++;
	//}
	//offsetImagePath[cnt] = '\0';
	//
}

void Grid::Update()
{

}

void Grid::Render(CRenderTarget* renderTarget)
{
	// test
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
	if (m_mouseClicked)	// mouse clicked
	{
		if (vSelected.x >= 0 && vSelected.x < vWorldSize.x && vSelected.y >= 0 && vSelected.y < vWorldSize.y)
		{
			pWorld[vSelected.y * vWorldSize.x + vSelected.x] = m_tileIndex;	// 이 위치의 타일을 바꿀 것.
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


void Grid::SetCurrentWorld(MyMap* world)
{
	currentWorld = world;
	if (world == nullptr) return;
	pWorld = (world->GetWorldData());
	vWorldSize = world->GetWorldSize();
}

COLORREF Grid::GetPixelColorFromBitmap(CBitmap* bitmap, int x, int y)
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

void Grid::SetTilePosByMouseClicked(int idx)
{
	m_mouseClicked = true;
	m_tileIndex = idx;
}

void Grid::ResetMouseClicked()
{
	m_mouseClicked = false;
	m_tileIndex = -1;
}

void Grid::ClearTiles()
{
	// 여기 좀 오류 있음..!
	for (auto& t : m_tiles)
	{
		if (t == nullptr) continue;
		delete t;
		t = nullptr;
	}
	m_tiles.clear();
	/*for (size_t i = 0; i < m_tiles.size(); ++i)
	{
		if (m_tiles[i] == nullptr) continue;
		delete m_tiles[i];
		m_tiles[i] = nullptr;
	}
	m_tiles.clear();*/
}
