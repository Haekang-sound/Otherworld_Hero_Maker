#pragma once

class MyMap;
class Tile;
class TileManager;
class NPCTileManager;

class DataControl
{
public:
	DataControl();
	~DataControl();

public:

	/// <summary>
	/// 맵을 추가합니다.
	/// </summary>
	/// <param name="map"></param>
	void AddMap(MyMap* map);

	/// <summary>
	/// 원하는 인덱스의 맵을 가져옵니다.
	/// </summary>
	/// <param name="idx"></param>
	/// <returns></returns>
	MyMap* GetMapByIndex(int idx);

	/// <summary>
	/// 지정한 인덱스의 맵을 지웁니다.
	/// </summary>
	/// <param name="idx"></param>
	void DeleteMapByIndex(int idx);

	/// <summary>
	/// 현재 맵의 개수를 반환합니다.
	/// </summary>
	/// <returns></returns>
	int GetMapCount() { return m_mapCount; }

	/// <summary>
	/// 타일 매니저를 가져옵니다.
	/// </summary>
	/// <returns></returns>
	TileManager* GetTileManager() { return m_tileManager; }

	/// <summary>
	/// 스프라이트르를 로드할 때 만들기 위해 렌더타겟을 저장한다.
	/// </summary>
	/// <param name="renderTarget"></param>
	void SetRenderTarget(CRenderTarget* renderTarget) { m_renderTarget = renderTarget; }

	/// <summary>
	/// 비트맵을 불러온다. 메인뷰의 렌더타겟이 사용된다.
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	CD2DBitmap* LoadBitmapByFilePath(CString filePath);

	/// <summary>
	/// 땅을 추가합니다.
	/// </summary>
	/// <param name="ground"></param>
	void AddGround(MyMap* ground);

	void DeleteGroundByIndex(int idx);
	MyMap* GetGroundByIndex(int idx);
	int GetGroundCount() { return m_groundCount; }
private:
	std::vector<MyMap*> m_maps;
	int m_mapCount = 0;

	std::vector<MyMap*> m_grounds;
	int m_groundCount = 0;

	TileManager* m_tileManager = nullptr;

	CRenderTarget* m_renderTarget = nullptr;
	// Save & Load
public:
	/// <summary>
	/// 툴에서 사용할 데이터 세이브
	/// </summary>
	void SaveData(CString path);

	/// <summary>
	/// 툴에서 사용할 데이터 로드
	/// </summary>
	void LoadData();

	/// <summary>
	/// 아래 맵, 그라운드 저장은 게임엔진을 위한 저장 방식임.
	/// </summary>
	/// <param name="path"></param>
	void SaveMap(CString path, int idx);
	void LoadMap(CString path);

	void SaveMapAll(CString path);
	void LoadMapAll(CString path);

	void SaveGround(CString path, int idx);
	void LoadGround(CString path);

	void SaveGroundAll(CString path);
	void LoadGroundAll(CString path);

	/// <summary>
	/// 타일 세이브.
	/// txt로 저장함.
	/// </summary>
	/// <param name="path"></param>
	void SaveTile(CString path);
	void LoadTile(CString path);




	/// <summary>
	/// 아래부터는 NPC 관리
	/// </summary>
public:
	void AddNPCLayer(MyMap* npcLayer);

	void DeleteNPCLayerByIndex(int idx);
	MyMap* GetNPCLayerByIndex(int idx);
	int GetNPCLayerCount() { return m_npcLayerCount; }

	void SaveNPCLayer(CString path, int idx);
	NPCTileManager* GetNPCTileManager() { return m_npcTileManager; }
private:
	std::vector<MyMap*> m_npcLayers;
	int m_npcLayerCount = 0;

	NPCTileManager* m_npcTileManager = nullptr;
};

