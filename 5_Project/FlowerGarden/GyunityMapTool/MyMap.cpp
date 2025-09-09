#include "pch.h"
#include "MyMap.h"
#include "Tile.h"
MyMap::MyMap()
{
	
}

MyMap::~MyMap()
{
	delete[] m_worldArray;
}

void MyMap::CreateMap(int worldSizeX, int worldSizeY, bool isNpcLayer /*= false*/)
{
	m_worldSize = { worldSizeX, worldSizeY };

	m_worldArray = new int[worldSizeX * worldSizeY];
	::memset(m_worldArray, -1, sizeof(int) * worldSizeX * worldSizeY);

	if (isNpcLayer == true)
	{
		m_npcWorldData = std::vector<std::vector<NpcWorldData>>(worldSizeY, std::vector<NpcWorldData>(worldSizeX));
		for (int y = 0; y < worldSizeY; y++)
		{
			for (int x = 0; x < worldSizeX; x++)
			{
				GetNpcWorldData()[y][x].npcIdx = -1;
				GetNpcWorldData()[y][x].npcPathCount = -1;
			}
		}
	}
}
