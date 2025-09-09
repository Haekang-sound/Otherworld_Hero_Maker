#include "TimeManager.h"

float TimeManager::m_timeScale = 1.f;

TimeManager::TimeManager()
	:m_deltaTime(0), m_fps(0),
	m_accumulationCount(0), m_accumulationTime(0),
	m_previousCount({}), m_frequency({})
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::Init()
{
	QueryPerformanceCounter(&m_previousCount);
}

void TimeManager::Update()
{
	// �̹� ������ Count ����
	LARGE_INTEGER currentCount;
	QueryPerformanceCounter(&currentCount);

	// �̹� ������ �� ����
	QueryPerformanceFrequency(&m_frequency);

	m_deltaTime = (currentCount.QuadPart - m_previousCount.QuadPart) / (float)m_frequency.QuadPart;
	m_previousCount = currentCount;
	
	// 1�� ���� �� �� ���� ���� ���� ������ ���� 1 �ø��� �ð� ����
	m_accumulationCount++;
	m_accumulationTime += m_deltaTime;

	// 1�ʰ� �Ǹ� �� �ʱ�ȭ
	if (m_accumulationTime >= 1.f)
	{
		m_fps = (int)(m_accumulationCount / m_accumulationTime);

		m_accumulationTime = 0.f;
		m_accumulationCount = 0;
	}
}
