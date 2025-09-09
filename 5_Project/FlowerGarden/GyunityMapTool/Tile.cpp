#include "pch.h"
#include "Tile.h"
#include "NPCGrid.h"
Tile::Tile()
{

}

Tile::~Tile()
{

}

void Tile::SetRelativePath(CString val)
{
	std::wstring path = CT2W(val);
	std::wstring RelativePathStart = L"GyunityMapTool\\resource";

	size_t foundIndex = path.find(RelativePathStart);

	// 찾는 문자열이 없을 경우
	if (foundIndex == std::wstring::npos)
	{
		return;
	}

	// 있으면 Resources 전까지 지움.
	path.erase(0, foundIndex);

	GetRelativePath();
	// ../ 추가
	m_relativePath = GetRelativePath() + L"../";

	// 경로 추가
	m_relativePath = GetRelativePath() + path;

	// \ -> /로 변경
	for (int i = 0; i < GetRelativePath().size(); i++)
	{
		if (GetRelativePath()[i] == '\\')
		{
			GetRelativePath()[i] = '/';
		}
	}

}
