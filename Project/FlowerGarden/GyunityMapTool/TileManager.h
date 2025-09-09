#pragma once

class Tile;
class TileManager
{
public:
	TileManager();
	~TileManager();

public:
	// Ÿ�� ����
	int GetTileCount() const { return m_tileCount; }
	// Ÿ�� �߰�
	void AddTile(Tile* tile);

	// ���� ����� ����?

	// ���ϴ� �ε����� Ÿ���� �ҷ���
	Tile* GetTileByIndex(int idx);

	void Clear();

private:

	std::vector<Tile*> m_tiles;
	int m_tileCount = 0;

};

