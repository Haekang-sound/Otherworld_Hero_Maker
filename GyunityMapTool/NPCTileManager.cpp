#include "pch.h"
#include "NPCTileManager.h"

NPCTileManager::NPCTileManager()
{

}

NPCTileManager::~NPCTileManager()
{

}

void NPCTileManager::AddTile(Tile* tile)
{
	m_tiles.push_back(tile);
	m_tileCount = GetTileCount() + 1;
}

Tile* NPCTileManager::GetTileByIndex(int idx)
{
	if (idx >= m_tileCount)
	{
		return nullptr;
	}

	return m_tiles[idx];
}

void NPCTileManager::Clear()
{
	m_tileCount = 0;
	for (auto& tile : m_tiles)
	{
		delete tile;
		tile = nullptr;
	}
	m_tiles.clear();
}
