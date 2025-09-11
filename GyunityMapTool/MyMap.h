#pragma once

class Tile;

struct NpcWorldData
{
	int npcIdx;
	int npcPathCount;
	int npcId;
};

class MyMap
{
public:
	MyMap();
	~MyMap();


	std::wstring GetName() const { return m_name; }
	void SetName(std::wstring val) { m_name = val; }

	void CreateMap(int worldSizeX, int worldSizeY, bool isNpcLayer = false);


	Vector2 GetWorldSize() const { return m_worldSize; }
	int* GetWorldData() { return m_worldArray; }

	std::vector<std::vector<NpcWorldData>> GetNpcWorldData() const { return GetNpcWorldData(); }
	void SetNpcWorldData(std::vector<std::vector<NpcWorldData>> val) { m_npcWorldData = val; }
	//void SetWorldSize(Vector2 val) { m_worldSize = val; }
	
	// Npc의 경로를 저장한 데이터를 가져옵니다.
	std::vector<std::vector<NpcWorldData>>& GetNpcWorldData() { return m_npcWorldData; }
private:
	std::wstring m_name;
	Vector2 m_worldSize = {};
	int* m_worldArray = nullptr;

	std::vector<std::vector<NpcWorldData>> m_npcWorldData;
};

