#pragma once

class Scene;
class DataControl
{
public:
	DataControl();
	~DataControl();

public:
	void AddSceneData(Scene* scene);
	void DeleteSceneDataByIndex(int idx);
	
	/// <summary>
	/// 모든 것을 없애버림
	/// </summary>
	void Clear();

	/// <summary>
	/// 지정한 인덱스의 씬을 가져옵니다.
	/// </summary>
	/// <param name="idx"></param>
	/// <returns></returns>
	Scene* GetSceneByIndex(int idx) { return m_scenes[idx]; }

	/// <summary>
	/// 씬의 개수
	/// </summary>
	/// <returns></returns>
	int GetSceneSize() { return m_scenes.size(); }

	/// <summary>
	/// 상대 경로 불러옴
	/// </summary>
	/// <returns></returns>
	std::wstring GetRelativePath() const { return m_relativePath; }

	/// <summary>
	/// 상대 경로 세팅
	/// </summary>
	/// <param name="val"></param>
	void SetRelativePath(std::wstring val) { m_relativePath = val; }

	/// <summary>
	/// 모든 씬의 상대 경로 세팅
	/// </summary>
	/// <param name="val"></param>
	void SetScenesRelativePath();
private:
	std::vector<Scene*> m_scenes;

	std::wstring m_relativePath;
	// 저장 관리
public:
	/// <summary>
	/// 게임엔진을 위한 상대경로 저장
	/// 폴더 경로를 받아오므로 내부에서 파일의 이름을 결정함
	/// </summary>
	void SaveSceneDataForGameEngine(CString folderPath, Scene* currentScene);

	/// <summary>
	/// 게임엔진을 위한 상대경로 저장. 모든 씬을 1개씩 추출한다.
	/// </summary>
	void SaveAllSceneDataForGameEngine(const CString& path);

	/// <summary>
	/// 툴의 세이브 데이터
	/// </summary>
	void SaveDataForTool(const CString& path);

	/// <summary>
	/// 현재 툴에서 관리하는 세이브데이터
	/// TODO : 파일을 로드할때 경로마다 파일이 실제로 있는지 확인할 것
	/// </summary>
	void LoadDataForTool(const CString& path);
};