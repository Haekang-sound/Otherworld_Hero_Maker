 /// 
/// 윈도우용 물리 엔진 시연 진입점
/// 

#include <windows.h>

#include "PhysicsDemo_Process.h"

// 메모리 누수 확인
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPWSTR lpCmdLine, 
	_In_ int nCmdShow) 
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = 0;

	LPCWSTR szWindowClass = L"PhysicsDemo";

	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = 0;

	RegisterClassExW(&wcex);

	// 윈도 핸들 생성
	HWND hWnd = CreateWindowW(
		szWindowClass, 
		L"물리 엔진 테스트",
		WS_OVERLAPPEDWINDOW, 
		0, 0, 
		SCREEN_WIDTH, SCREEN_HEIGHT,
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 메모리 누수 확인 
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	// 게임 초기화 부분
	PhysicsDemoProcess* physicsDemo;
	physicsDemo = new PhysicsDemoProcess;
	physicsDemo->Initialize(hWnd);
	physicsDemo->SetScreenSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				break;
			}

			if (msg.message == WM_QUIT)
			{
				break;
			}

			DispatchMessage(&msg);
		}
		else
		{
			// 게임 루프 부분
			physicsDemo->Loop();
		}
	}

	// 게임 종료 부분
	physicsDemo->Finalize();
	delete physicsDemo;

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;

	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}

	return 0;
}
