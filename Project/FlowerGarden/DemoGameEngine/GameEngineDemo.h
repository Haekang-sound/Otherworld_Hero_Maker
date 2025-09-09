#pragma once

#include <windows.h>

// Engine
class DirectY;
class WinAPIInit;

// Manager
class GameEngine;
class TileManager;

/// <summary>
/// 엔진 초기화, Update 및 Render를 담당한다.
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

