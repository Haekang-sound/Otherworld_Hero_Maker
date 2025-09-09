#include "WinAPIInit.h"
#include "InputManager.h"

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
	case WM_MOUSEWHEEL:
	{
		int zDelta = GET_WHEEL_DELTA_WPARAM(wParam); // �� ȸ�� ũ��
		//short keyState = GET_KEYSTATE_WPARAM(wParam); // ���� ���� ���� Ű ���� (Ctrl, Shift ��)

		//int x = LOWORD(lParam); // ���콺 X ��ǥ
		//int y = HIWORD(lParam); // ���콺 Y ��ǥ

		InputManager::GetInstance().SetWheelPower(zDelta);

		return 0;
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
		WS_POPUP,
		0,
		0,
		1920,
		1080,
		NULL,
		NULL,
		hInstance,
		nullptr);

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	return TRUE;
}
