#include "pch.h"
#include "TileManager.h"
#include "Tile.h"

TileManager::TileManager()
{

}

TileManager::~TileManager()
{

}

void TileManager::AddTile(Tile* tile)
{
	m_tiles.push_back(tile);
	m_tileCount = GetTileCount() + 1;
}

Tile* TileManager::GetTileByIndex(int idx)
{
	if (idx >= m_tileCount)
	{
		return nullptr;
	}

	return m_tiles[idx];
}

void TileManager::Clear()
{
	m_tileCount = 0;
// 	for (auto& tile : m_tiles)
// 	{
// 		delete tile;
// 		tile = nullptr;
// 	}
	m_tiles.clear();
}
