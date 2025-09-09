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
	/// ��� ���� ���ֹ���
	/// </summary>
	void Clear();

	/// <summary>
	/// ������ �ε����� ���� �����ɴϴ�.
	/// </summary>
	/// <param name="idx"></param>
	/// <returns></returns>
	Scene* GetSceneByIndex(int idx) { return m_scenes[idx]; }

	/// <summary>
	/// ���� ����
	/// </summary>
	/// <returns></returns>
	int GetSceneSize() { return m_scenes.size(); }

	/// <summary>
	/// ��� ��� �ҷ���
	/// </summary>
	/// <returns></returns>
	std::wstring GetRelativePath() const { return m_relativePath; }

	/// <summary>
	/// ��� ��� ����
	/// </summary>
	/// <param name="val"></param>
	void SetRelativePath(std::wstring val) { m_relativePath = val; }

	/// <summary>
	/// ��� ���� ��� ��� ����
	/// </summary>
	/// <param name="val"></param>
	void SetScenesRelativePath();
private:
	std::vector<Scene*> m_scenes;

	std::wstring m_relativePath;
	// ���� ����
public:
	/// <summary>
	/// ���ӿ����� ���� ����� ����
	/// ���� ��θ� �޾ƿ��Ƿ� ���ο��� ������ �̸��� ������
	/// </summary>
	void SaveSceneDataForGameEngine(CString folderPath, Scene* currentScene);

	/// <summary>
	/// ���ӿ����� ���� ����� ����. ��� ���� 1���� �����Ѵ�.
	/// </summary>
	void SaveAllSceneDataForGameEngine(const CString& path);

	/// <summary>
	/// ���� ���̺� ������
	/// </summary>
	void SaveDataForTool(const CString& path);

	/// <summary>
	/// ���� ������ �����ϴ� ���̺굥����
	/// TODO : ������ �ε��Ҷ� ��θ��� ������ ������ �ִ��� Ȯ���� ��
	/// </summary>
	void LoadDataForTool(const CString& path);
};