#pragma once


// �̰Ŵ� ���� �Ⱦ�
const float g_mainImagePosX = 300.f;
const float g_mainImagePosY = 300.f;


// ���α׷� ó�� ���� ��ġ
const int g_programPosX = 0;
const int g_programPosY = 0;
// ���� ���α׷� ������ ����
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