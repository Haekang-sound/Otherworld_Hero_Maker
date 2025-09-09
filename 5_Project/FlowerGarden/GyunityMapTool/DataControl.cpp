#include "pch.h"
#include "DataControl.h"
#include "MyMap.h"
#include "TileManager.h"
#include "Tile.h"
#include "NPCTileManager.h"

DataControl::DataControl()
{
	m_tileManager = new TileManager();
	m_npcTileManager = new NPCTileManager();
}

DataControl::~DataControl()
{
	m_tileManager->Clear();
	delete m_tileManager;

	m_npcTileManager->Clear();
	delete m_npcTileManager;
}

void DataControl::AddMap(MyMap* map)
{
	m_maps.push_back(map);
	m_mapCount++;
}

MyMap* DataControl::GetMapByIndex(int idx)
{
	if (m_maps[idx] == nullptr)
		return nullptr;

	return m_maps[idx];
}

void DataControl::DeleteMapByIndex(int idx)
{
	if (m_mapCount == 0)
		return;

	m_maps.erase(m_maps.begin() + idx);
	m_mapCount--;
}

CD2DBitmap* DataControl::LoadBitmapByFilePath(CString filePath)
{
	HINSTANCE hResInstance = AfxGetResourceHandle();
	CD2DBitmap* newBitmap = new CD2DBitmap(m_renderTarget, filePath, CD2DSizeU(0, 0), TRUE);
	newBitmap->Create(m_renderTarget);
	AfxSetResourceHandle(hResInstance);
	return newBitmap;
}

void DataControl::AddGround(MyMap* ground)
{
	m_grounds.push_back(ground);
	m_groundCount++;
}

void DataControl::DeleteGroundByIndex(int idx)
{
	if (m_groundCount == 0)
		return;

	m_grounds.erase(m_grounds.begin() + idx);
	m_groundCount--;
}

MyMap* DataControl::GetGroundByIndex(int idx)
{
	if (m_grounds[idx] == nullptr)
		return nullptr;

	return m_grounds[idx];
}

void DataControl::SaveData(CString path)
{

}

void DataControl::LoadData()
{

}

void DataControl::SaveMap(CString path, int idx)
{
	std::wofstream ofs;
	ofs.open(path);

	MyMap* map = GetMapByIndex(idx);
	int* mapArray = map->GetWorldData();
	Vector2 mapSize = map->GetWorldSize();

	// 맵 이름
	ofs << map->GetName() << std::endl;
	// 행
	ofs << L"col " << mapSize.y << std::endl;
	// 열
	ofs << L"row " << mapSize.x << std::endl;

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			ofs << mapArray[y * mapSize.x + x] << ' ';
		}
		ofs << std::endl;
	}
	ofs.close();
}

void DataControl::LoadMap(CString path)
{
	std::wifstream ifs;
	ifs.open(path);

	std::wstring mapName;
	ifs >> mapName;
	std::wstring temp;
	float size;
	ifs >> temp >> temp >> temp >> size;

	MyMap* newMap = new MyMap();
	newMap->SetName(mapName);
	newMap->CreateMap(size, size);

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			int idx = y * size + x;
			ifs >> newMap->GetWorldData()[idx];
		}
	}


	newMap->SetName(mapName);

	AddMap(newMap);
}

void DataControl::SaveMapAll(CString path)
{

	int mapCount = m_mapCount;
	for (int i = 0; i < mapCount; i++)
	{
		CString filePath = path;
		filePath.Append(_T("\\"));
		filePath.Append(GetMapByIndex(i)->GetName().c_str());
		filePath.Append(_T(".txt"));

		std::wofstream ofs;
		ofs.open(filePath);

		MyMap* map = GetMapByIndex(i);
		int* mapArray = map->GetWorldData();
		Vector2 mapSize = map->GetWorldSize();

		// 맵 이름
		ofs << map->GetName() << std::endl;
		// 행
		ofs << L"col " << mapSize.y << std::endl;
		// 열
		ofs << L"row " << mapSize.x << std::endl;

		for (int y = 0; y < mapSize.y; y++)
		{
			for (int x = 0; x < mapSize.x; x++)
			{
				ofs << mapArray[y * mapSize.x + x] << ' ';
			}
			ofs << std::endl;
		}
		ofs.close();
	}
}

void DataControl::LoadMapAll(CString path)
{

}

void DataControl::SaveGround(CString path, int idx)
{
	std::wofstream ofs;
	ofs.open(path);

	MyMap* ground = GetGroundByIndex(idx);
	int* mapArray = ground->GetWorldData();
	Vector2 mapSize = ground->GetWorldSize();

	// 맵 이름
	ofs << ground->GetName() << std::endl;
	// 행
	ofs << L"col " << mapSize.y << std::endl;
	// 열
	ofs << L"row " << mapSize.x << std::endl;

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			ofs << mapArray[y * mapSize.x + x] << ' ';
		}
		ofs << std::endl;
	}
	ofs.close();
}

void DataControl::LoadGround(CString path)
{
	std::wifstream ifs;
	ifs.open(path);

	std::wstring mapName;
	ifs >> mapName;
	std::wstring temp;
	float size;
	ifs >> temp >> temp >> temp >> size;

	MyMap* newMap = new MyMap();
	newMap->SetName(mapName);
	newMap->CreateMap(size, size);

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			int idx = y * size + x;
			ifs >> newMap->GetWorldData()[idx];
		}
	}


	newMap->SetName(mapName);

	AddGround(newMap);
}

void DataControl::SaveGroundAll(CString path)
{
	int groundCount = m_mapCount;
	for (int i = 0; i < groundCount; i++)
	{
		CString filePath = path;
		filePath.Append(_T("\\"));
		filePath.Append(GetGroundByIndex(i)->GetName().c_str());
		filePath.Append(_T(".txt"));

		std::wofstream ofs;
		ofs.open(filePath);

		MyMap* ground = GetGroundByIndex(i);
		int* mapArray = ground->GetWorldData();
		Vector2 mapSize = ground->GetWorldSize();

		// 맵 이름
		ofs << ground->GetName() << std::endl;
		// 행
		ofs << L"col " << mapSize.y << std::endl;
		// 열
		ofs << L"row " << mapSize.x << std::endl;

		for (int y = 0; y < mapSize.y; y++)
		{
			for (int x = 0; x < mapSize.x; x++)
			{
				ofs << mapArray[y * mapSize.x + x] << ' ';
			}
			ofs << std::endl;
		}
		ofs.close();
	}
}

void DataControl::LoadGroundAll(CString path)
{

}

void DataControl::SaveTile(CString path)
{
	std::wofstream ofs;
	ofs.open(path);

	int tileCount = m_tileManager->GetTileCount();

	// 타일 개수
	ofs << tileCount << std::endl;
	for (int i = 0; i < tileCount; i++)
	{
		Tile* tile = m_tileManager->GetTileByIndex(i);
		ofs << m_tileManager->GetTileByIndex(i)->GetName() << std::endl;
		//1.0//ofs << std::wstring(m_tileManager->GetTileByIndex(i)->GetFilePath()) << std::endl;
		ofs << std::wstring(m_tileManager->GetTileByIndex(i)->GetRelativePath()) << std::endl;
	}

	ofs.close();
}

void DataControl::LoadTile(CString path)
{
	// Clear부터 함.
	m_tileManager->Clear();


	std::wifstream ifs;
	ifs.open(path);

	int tileCount = 0;
	ifs >> tileCount;
	for (int i = 0; i < tileCount; i++)
	{
		Tile* newTile = new Tile();

		// 이름 받아옴
		std::wstring tileName;
		ifs >> tileName;
		newTile->SetName(tileName);

		// 파일 경로 받아옴.
		std::wstring filePath;
		ifs >> filePath;
		newTile->SetFilePath(filePath.c_str());

		// 파일이 없을경우 그 파일은 로드를 안 함
		{
			CFileFind finder;
			if (finder.FindFile(filePath.c_str()) == false)
			{
				finder.Close();
				continue;
			}
			finder.Close();
		}

		// 받아온 파일 경로로 비트맵을 로드함.
		CD2DBitmap* bitmap = LoadBitmapByFilePath(filePath.c_str());
		newTile->SetBitmap(bitmap);

		m_tileManager->AddTile(newTile);
	}

	ifs.close();
}

void DataControl::AddNPCLayer(MyMap* npcLayer)
{
	m_npcLayers.push_back(npcLayer);
	m_npcLayerCount++;
}

void DataControl::DeleteNPCLayerByIndex(int idx)
{
	if (m_npcLayerCount == 0)
		return;

	m_npcLayers.erase(m_npcLayers.begin() + idx);
	m_npcLayerCount--;
}

MyMap* DataControl::GetNPCLayerByIndex(int idx)
{
	if (m_npcLayers[idx] == nullptr)
		return nullptr;

	return m_npcLayers[idx];
}

void DataControl::SaveNPCLayer(CString path, int idx)
{
	std::wofstream ofs;
	ofs.open(path);

	MyMap* map = GetNPCLayerByIndex(idx);
	int* mapArray = map->GetWorldData();
	Vector2 mapSize = map->GetWorldSize();

	// 맵 이름
	ofs << map->GetName() << std::endl;
	// 행
	ofs << L"col " << mapSize.y << std::endl;
	// 열
	ofs << L"row " << mapSize.x << std::endl;

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			ofs << map->GetNpcWorldData()[y][x].npcIdx << ' ' << map->GetNpcWorldData()[y][x].npcPathCount << ' '
				<< map->GetNpcWorldData()[y][x].npcId << ' ';
		}
		ofs << std::endl;
	}
	ofs.close();
}
