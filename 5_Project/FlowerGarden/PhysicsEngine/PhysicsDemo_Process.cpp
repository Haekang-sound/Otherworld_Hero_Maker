#include "PhysicsDemo_Process.h"
#include "Object.h"
#include "Vector2.h"
#include "Vector2.h"
#include "Solver.h"
#include "PositionSolver.h"
#include "MathUtils.h"

#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "IsometricCollider.h"
#include "VehicleCollider.h"

using namespace MathEngine;
using namespace PhysicsEngine;

PhysicsDemoProcess::PhysicsDemoProcess()
	: m_frequency{ 0 }
	, m_preTime{ 0 }
	, m_curTime{ 0 }
	, m_ScreenWidth(1920.f)
	, m_ScreenHeight(1080.f)
	, m_frame(0.0166666f) // 60 프레임
	, m_deltaTime(0.0f)
	, m_fps(0.0f)
	, m_accumulationCount(0.0f)
	, m_accumulationTime(0.0f)
	, m_graphicEngine(nullptr)
	, m_player(nullptr)
	, m_obstacle(nullptr)
	, degree(0.f)
{

}

PhysicsDemoProcess::~PhysicsDemoProcess()
{

}

void PhysicsDemoProcess::Initialize(HWND hwnd)
{
	m_graphicEngine = new DirectY(hwnd);
	
	float centerPosX = m_ScreenWidth / 2.f;
	float centerPosY = m_ScreenHeight / 2.f;

	// Player
	m_player = new VehicleCollider(m_ScreenWidth / 2.f, m_ScreenHeight / 2.f, 100.f);
	// Obstacle
	m_obstacle = new PhysicsEngine::IsometricCollider(1080.f, 500.f);
}

void PhysicsDemoProcess::Loop()
{
	/// 시간 측정
	QueryPerformanceCounter(&m_curTime);
	QueryPerformanceFrequency(&m_frequency);

	// dt
	m_deltaTime = 
		(m_curTime.QuadPart - m_preTime.QuadPart) /
		(float)m_frequency.QuadPart;
	m_preTime = m_curTime;

	// fps
	m_accumulationCount++;
	m_accumulationTime += m_deltaTime;
	if (m_accumulationCount > m_frame)
	{
		m_fps = (m_accumulationCount / m_accumulationTime);
		m_accumulationTime = 0.f;
		m_accumulationCount = 0;
	}

	/// 실제 게임 진행 및 그리기
	m_graphicEngine->BeginDraw();
	m_graphicEngine->CleanWindow();

	Update();
	Render();

	m_graphicEngine->EndDraw();
}

void PhysicsDemoProcess::Update()
{
	/// 외부 처리
	// 마우스 입력에 따른 이동및 기타 처리
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			degree += 1.f;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			degree -= 1.f;
		}
		if (GetAsyncKeyState(0x57) & 0x8000) // W
		{
			m_player->initCenter += Vector2(0.f, -1.f);
		}
		if (GetAsyncKeyState(0x41) & 0x8000) // A
		{
			m_player->initCenter += Vector2(-1.f, 0.f);
		}
		if (GetAsyncKeyState(0x53) & 0x8000) // S
		{
			m_player->initCenter += Vector2(0.f, 1.f);
		}
		if (GetAsyncKeyState(0x44) & 0x8000) // D
		{
			m_player->initCenter += Vector2(1.f, 0.f);
		}
	}

	// 좌상 대각선
	if (0 < degree && degree > 30)
	{
		m_player->points[0] = Vector2(m_player->initCenter.x - m_player->width / 4.f, m_player->initCenter.y - m_player->height / 2.f);
		m_player->points[1] = Vector2(m_player->initCenter.x - m_player->width / 2.f, m_player->initCenter.y);
		m_player->points[2] = Vector2(m_player->initCenter.x + m_player->width / 4.f, m_player->initCenter.y + m_player->height / 2.f);
		m_player->points[3] = Vector2(m_player->initCenter.x + m_player->width / 2.f, m_player->initCenter.y);

	}
	// 정면
	if (30 < degree && degree > 60)
	{
		m_player->points[0] = Vector2(m_player->initCenter.x - m_player->width / 4.f, m_player->initCenter.y - m_player->height / 4.f);
		m_player->points[1] = Vector2(m_player->initCenter.x - m_player->width / 4.f, m_player->initCenter.y + m_player->height / 2.f);
		m_player->points[2] = Vector2(m_player->initCenter.x + m_player->width / 4.f, m_player->initCenter.y + m_player->height / 2.f);
		m_player->points[3] = Vector2(m_player->initCenter.x + m_player->width / 4.f, m_player->initCenter.y - m_player->height / 4.f);
	}
	// 우상 대각선
	if (60 < degree && degree > 90)
	{
		m_player->points[0] = Vector2(m_player->initCenter.x - m_player->width / 2.f, m_player->initCenter.y);
		m_player->points[1] = Vector2(m_player->initCenter.x - m_player->width / 4.f, m_player->initCenter.y + m_player->height / 2.f);
		m_player->points[2] = Vector2(m_player->initCenter.x + m_player->width / 2.f, m_player->initCenter.y);
		m_player->points[3] = Vector2(m_player->initCenter.x + m_player->width / 4.f, m_player->initCenter.y - m_player->height / 2.f);
	}
	// 측면
	if (90 < degree && degree > 120)
	{
		m_player->points[0] = Vector2(m_player->initCenter.x - m_player->width / 3.f, m_player->initCenter.y - m_player->height / 4.f);
		m_player->points[1] = Vector2(m_player->initCenter.x - m_player->width / 3.f, m_player->initCenter.y + m_player->height / 3.f);
		m_player->points[2] = Vector2(m_player->initCenter.x + m_player->width / 3.f, m_player->initCenter.y + m_player->height / 3.f);
		m_player->points[3] = Vector2(m_player->initCenter.x + m_player->width / 3.f, m_player->initCenter.y - m_player->height / 4.f);
	}

	if (degree > 120.f)
	{
		degree = 0.f;
	}

	if (degree < 0.f)
	{
		degree = 120.f;
	}

	m_player->center = m_player->initCenter;
}

void PhysicsDemoProcess::Render()
{
	m_graphicEngine->SetBrushColor(D2D1::ColorF::AntiqueWhite);

	if (m_player->TestCollision(*m_obstacle).hasCollision)
	{
		m_graphicEngine->SetBrushColor(D2D1::ColorF::Red);
	}
	else
	{
		m_graphicEngine->SetBrushColor(D2D1::ColorF::Green);
	}
	m_player->DrawCollider(*m_graphicEngine);
	m_obstacle->DrawCollider(*m_graphicEngine);

	m_graphicEngine->SetBrushColor(D2D1::ColorF::Red);
	m_graphicEngine->DrawCircle(Graphics::BaseFigure::Circle{m_player->points[0].x, m_player->points[0].y, 1.f}, 10.f);
}

void PhysicsDemoProcess::Finalize()
{ 
	if (m_graphicEngine) delete m_graphicEngine;

	if (m_player) delete m_player;
}