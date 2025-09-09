#pragma once
class MyFile
{
public:
	MyFile();
	~MyFile();


	CString GetPath() const { return m_path; }

	/// <summary>
	/// ���� ��θ� ������ �� ��� ��ε� ������.
	/// </summary>
	/// <param name="val"></param>
	void SetPath(CString val) { m_path = val; SetRelativePath(val); }

	std::wstring GetName() const { return m_name; }
	void SetName(std::wstring val) { m_name = val; }

	std::wstring GetRelativePath() const { return m_relativePath; }
	//void SetRelativePath(std::wstring val) { m_relativePath = val; }

	/// <summary>
	/// CString�� �����θ� wstring�� ����η� �ٲپ �����Ѵ�.
	/// </summary>
	/// <param name="val"></param>
	void SetRelativePath(CString val);
private:
	std::wstring m_name;
	CString m_path;
	std::wstring m_relativePath;
};

