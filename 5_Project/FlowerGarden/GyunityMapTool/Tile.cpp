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

	// ã�� ���ڿ��� ���� ���
	if (foundIndex == std::wstring::npos)
	{
		return;
	}

	// ������ Resources ������ ����.
	path.erase(0, foundIndex);

	GetRelativePath();
	// ../ �߰�
	m_relativePath = GetRelativePath() + L"../";

	// ��� �߰�
	m_relativePath = GetRelativePath() + path;

	// \ -> /�� ����
	for (int i = 0; i < GetRelativePath().size(); i++)
	{
		if (GetRelativePath()[i] == '\\')
		{
			GetRelativePath()[i] = '/';
		}
	}

}
