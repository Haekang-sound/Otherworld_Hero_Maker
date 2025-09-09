#include "pch.h"
#include "MyFile.h"
#include "Global.h"
MyFile::MyFile()
{

}

MyFile::~MyFile()
{

}

void MyFile::SetRelativePath(CString val)
{
	std::wstring path = CT2W(val);
	std::wstring RelativePathStart = g_relativePath;

	size_t foundIndex = path.find(RelativePathStart);

	// ã�� ���ڿ��� ���� ���
	if (foundIndex == std::wstring::npos)
	{
		return;
	}
	
	// ������ Resources ������ ����.
	path.erase(0, foundIndex);

	// ../ �߰�
	m_relativePath += L"../";

	// ��� �߰�
	m_relativePath += path;

	// \ -> /�� ����
	for (int i = 0; i < m_relativePath.size(); i++)
	{
		if (m_relativePath[i] == '\\')
		{
			m_relativePath[i] = '/';
		}
	}

	//int a = 3;
}
