#pragma once

/// <summary>
/// Ÿ���� �����ͷ� ��� �ִ� �귯��
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

