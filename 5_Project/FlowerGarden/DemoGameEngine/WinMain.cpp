#include <SDKDDKVer.h>

// Windows ��� ����
#include <windows.h>
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#include "GameEngineDemo.h"

#include <crtdbg.h>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(519);

	GameEngineDemo* gameProcess = new GameEngineDemo;

	gameProcess->Init(hInstance);
	gameProcess->Loop();
	gameProcess->Release();

	delete gameProcess;

	return 0;
}