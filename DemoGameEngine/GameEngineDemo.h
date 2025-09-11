#pragma once

#include <windows.h>

// Engine
class DirectY;
class WinAPIInit;

// Manager
class GameEngine;
class TileManager;

/// <summary>
/// ���� �ʱ�ȭ, Update �� Render�� ����Ѵ�.
/// </summary>
class GameEngineDemo
{
public:
	GameEngineDemo();
	~GameEngineDemo();

	void Init(HINSTANCE hInstance);
	void Loop();
	void Release();

	void FixedUpdate();
	void Update();
	void LateUpdate();

	void PreRender();
	void Render();
	void PostRender();

private:
	HWND m_hWnd;

	WinAPIInit*	m_winAPIInit;
	DirectY*	m_directY;
	
	GameEngine* m_gameEngine;
	TileManager* m_tileManger;
};

