/// 
/// 물리 엔진의 시연의 진행을 담당하는 클래스
/// 

#pragma once

#include <windows.h>

#include "DirectY.h"
#include "PhysicsWorld.h"

namespace PhysicsEngine 
{ 
	struct VehicleCollider; 
	struct IsometricCollider;
}

class PhysicsDemoProcess
{
public:
	PhysicsDemoProcess();
	~PhysicsDemoProcess();

public:
	void Initialize(HWND g_hwind);
	void Loop();
	void Finalize();

	void SetScreenSize(float w, float h)
	{
		m_ScreenWidth = w;
		m_ScreenHeight = h;
	}

private:
	// 화면 크기
	float m_ScreenWidth;
	float m_ScreenHeight;

	// 프레임 조절
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_preTime;
	LARGE_INTEGER m_curTime;
	const float m_frame;
	float m_deltaTime;
	float m_fps;
	float m_accumulationCount;
	float m_accumulationTime;

	// 외부 객체
	DirectY* m_graphicEngine;

	// 테스트 객체
	PhysicsEngine::VehicleCollider* m_player;
	PhysicsEngine::IsometricCollider* m_obstacle;

	// 기타 변수
	float degree;

	void Render();
	void Update();
};