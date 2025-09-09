#pragma once

class MyFile;
class Scene
{
public:
	Scene();
	~Scene();

	void Clear();

	void SetSceneName(const std::wstring& name) { m_sceneName = name; }
	std::wstring GetSceneName() { return m_sceneName; }
	/// <summary>
	/// ���ο� ������ ���� �߰��մϴ�.
	/// </summary>
	/// <param name="file"></param>
	void AddFile(MyFile* file);

	/// <summary>
	/// �Էµ� �ε����� ������ ����ϴ�.
	/// </summary>
	/// <param name="idx"></param>
	void DeleteFileByIndex(int idx);

	int GetFileCount() { return m_fileCount; }

	MyFile* GetFileByIndex(int idx) { return m_files[idx]; }

	void SetRelativePath();
private:
	std::wstring m_sceneName;
	std::vector<MyFile*> m_files;

	int m_fileCount = 0;
};

