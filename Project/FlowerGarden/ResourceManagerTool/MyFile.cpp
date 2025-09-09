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

	// 찾는 문자열이 없을 경우
	if (foundIndex == std::wstring::npos)
	{
		return;
	}
	
	// 있으면 Resources 전까지 지움.
	path.erase(0, foundIndex);

	// ../ 추가
	m_relativePath += L"../";

	// 경로 추가
	m_relativePath += path;

	// \ -> /로 변경
	for (int i = 0; i < m_relativePath.size(); i++)
	{
		if (m_relativePath[i] == '\\')
		{
			m_relativePath[i] = '/';
		}
	}

	//int a = 3;
}
