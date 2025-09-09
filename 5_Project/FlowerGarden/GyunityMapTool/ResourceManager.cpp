#include "pch.h"
#include "ResourceManager.h"

std::wstring ResourceManager::GetImagePath(std::wstring path)
{
	TCHAR offsetImagePath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, offsetImagePath);

	int cnt = 0;
	while (offsetImagePath[cnt] != '\0')
	{
		cnt++;
	}
	while (offsetImagePath[cnt] != '\\')
	{
		//offsetImagePath[cnt] = '\0';
		cnt--;
	}
	cnt++;
	//cnt++;
	//offsetImagePath[cnt + 1] = '\0';
	//std::wstring addPath(L"GunityMapTool\\resource\\pos.png");
	std::wstring addPath(L"GyunityMapTool\\resource\\");
	addPath += path;
	for (int i = 0; i < addPath.size(); i++)
	{
		offsetImagePath[cnt] = addPath[i];
		cnt++;
	}
	offsetImagePath[cnt] = '\0';

	return offsetImagePath;
}
