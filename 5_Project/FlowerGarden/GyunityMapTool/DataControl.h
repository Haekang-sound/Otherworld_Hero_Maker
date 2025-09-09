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
	/// ���� �߰��մϴ�.
	/// </summary>
	/// <param name="map"></param>
	void AddMap(MyMap* map);

	/// <summary>
	/// ���ϴ� �ε����� ���� �����ɴϴ�.
	/// </summary>
	/// <param name="idx"></param>
	/// <returns></returns>
	MyMap* GetMapByIndex(int idx);

	/// <summary>
	/// ������ �ε����� ���� ����ϴ�.
	/// </summary>
	/// <param name="idx"></param>
	void DeleteMapByIndex(int idx);

	/// <summary>
	/// ���� ���� ������ ��ȯ�մϴ�.
	/// </summary>
	/// <returns></returns>
	int GetMapCount() { return m_mapCount; }

	/// <summary>
	/// Ÿ�� �Ŵ����� �����ɴϴ�.
	/// </summary>
	/// <returns></returns>
	TileManager* GetTileManager() { return m_tileManager; }

	/// <summary>
	/// ��������Ʈ���� �ε��� �� ����� ���� ����Ÿ���� �����Ѵ�.
	/// </summary>
	/// <param name="renderTarget"></param>
	void SetRenderTarget(CRenderTarget* renderTarget) { m_renderTarget = renderTarget; }

	/// <summary>
	/// ��Ʈ���� �ҷ��´�. ���κ��� ����Ÿ���� ���ȴ�.
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	CD2DBitmap* LoadBitmapByFilePath(CString filePath);

	/// <summary>
	/// ���� �߰��մϴ�.
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
	/// ������ ����� ������ ���̺�
	/// </summary>
	void SaveData(CString path);

	/// <summary>
	/// ������ ����� ������ �ε�
	/// </summary>
	void LoadData();

	/// <summary>
	/// �Ʒ� ��, �׶��� ������ ���ӿ����� ���� ���� �����.
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
	/// Ÿ�� ���̺�.
	/// txt�� ������.
	/// </summary>
	/// <param name="path"></param>
	void SaveTile(CString path);
	void LoadTile(CString path);




	/// <summary>
	/// �Ʒ����ʹ� NPC ����
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

