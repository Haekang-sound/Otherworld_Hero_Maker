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
	/// 새로운 파일을 씬에 추가합니다.
	/// </summary>
	/// <param name="file"></param>
	void AddFile(MyFile* file);

	/// <summary>
	/// 입력된 인덱스의 파일을 지웁니다.
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

