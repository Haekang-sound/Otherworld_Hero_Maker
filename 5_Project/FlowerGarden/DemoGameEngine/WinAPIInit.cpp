#include "WinAPIInit.h"

WinAPIInit::WinAPIInit()
	:m_hInst(NULL), m_hWnd(NULL)
{

}

WinAPIInit::~WinAPIInit()
{

}

HWND WinAPIInit::Init(HINSTANCE hInstance)
{
	MyRegisterClass(hInstance);
	InitInstance(hInstance);

	return m_hWnd;
}

/// <summary>
/// 
/// </summary>
/// <returns> false: GetMessage WM_QUIT</returns>
MSG WinAPIInit::ProcessMessage()
{
	MSG msg = {};

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		DispatchMessage(&msg);
	}

	return msg;
}

void WinAPIInit::Release()
{

}

LRESULT CALLBACK WinAPIInit::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void WinAPIInit::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = hInstance;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wcex.lpszClassName = L"D2DDemoApp";

	RegisterClassEx(&wcex);
}

BOOL WinAPIInit::InitInstance(HINSTANCE hInstance)
{
	m_hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	m_hWnd = CreateWindow(
		L"D2DDemoApp",
		L"Direct2D demo application",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		NULL,
		NULL,
		hInstance,
		nullptr);

	// Because the SetWindowPos function takes its size in pixels, we
	// obtain the window's DPI, and use it to scale the window size.
	float dpi = (float)GetDpiForWindow(m_hWnd);

	SetWindowPos(
		m_hWnd,
		NULL,
		NULL,
		NULL,
		static_cast<int>(1920),
		static_cast<int>(1080),
		SWP_NOMOVE);
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	return TRUE;
}
