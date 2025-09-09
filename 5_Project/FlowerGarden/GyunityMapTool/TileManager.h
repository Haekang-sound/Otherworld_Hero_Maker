#pragma once

class Tile;
class TileManager
{
public:
	TileManager();
	~TileManager();

public:
	// 타일 개수
	int GetTileCount() const { return m_tileCount; }
	// 타일 추가
	void AddTile(Tile* tile);

	// 삭제 기능은 굳이?

	// 원하는 인덱스의 타일을 불러옴
	Tile* GetTileByIndex(int idx);

	void Clear();

private:

	std::vector<Tile*> m_tiles;
	int m_tileCount = 0;

};

