#pragma once


// 이거는 아직 안씀
const float g_mainImagePosX = 300.f;
const float g_mainImagePosY = 300.f;


// 프로그램 처음 실행 위치
const int g_programPosX = 0;
const int g_programPosY = 0;
// 메인 프로그램 사이즈 정의
const int g_programSizeX = 1920;
const int g_programSizeY = 1080;


template<class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}