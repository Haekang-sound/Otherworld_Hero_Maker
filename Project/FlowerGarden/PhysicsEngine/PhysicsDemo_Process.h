/// 
/// ���� ������ �ÿ��� ������ ����ϴ� Ŭ����
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
	// ȭ�� ũ��
	float m_ScreenWidth;
	float m_ScreenHeight;

	// ������ ����
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_preTime;
	LARGE_INTEGER m_curTime;
	const float m_frame;
	float m_deltaTime;
	float m_fps;
	float m_accumulationCount;
	float m_accumulationTime;

	// �ܺ� ��ü
	DirectY* m_graphicEngine;

	// �׽�Ʈ ��ü
	PhysicsEngine::VehicleCollider* m_player;
	PhysicsEngine::IsometricCollider* m_obstacle;

	// ��Ÿ ����
	float degree;

	void Render();
	void Update();
};