#pragma once

/// <summary>
/// 타일을 포인터로 들고 있는 브러쉬
/// </summary>

class Tile;
class TileBrush
{
public:
	TileBrush();
	TileBrush(Tile* tile);
	~TileBrush();



	Tile* GetTile() const { return m_tile; }
	void SetTile(Tile* val) { m_tile = val; }
private:
	Tile* m_tile;
};

