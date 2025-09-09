#pragma once
class MyFile
{
public:
	MyFile();
	~MyFile();


	CString GetPath() const { return m_path; }

	/// <summary>
	/// 절대 경로를 지정할 떄 상대 경로도 지정함.
	/// </summary>
	/// <param name="val"></param>
	void SetPath(CString val) { m_path = val; SetRelativePath(val); }

	std::wstring GetName() const { return m_name; }
	void SetName(std::wstring val) { m_name = val; }

	std::wstring GetRelativePath() const { return m_relativePath; }
	//void SetRelativePath(std::wstring val) { m_relativePath = val; }

	/// <summary>
	/// CString의 절대경로를 wstring의 상대경로로 바꾸어서 저장한다.
	/// </summary>
	/// <param name="val"></param>
	void SetRelativePath(CString val);
private:
	std::wstring m_name;
	CString m_path;
	std::wstring m_relativePath;
};

