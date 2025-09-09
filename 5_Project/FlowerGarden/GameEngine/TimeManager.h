#pragma once
#include <windows.h>

// #include <chrono> �ð� ���� ���̺귯�� �ð� ���� Ȯ���غ���

/// <summary>
/// DeltaTime�� �����ϱ� ���� Ŭ����
/// 
/// 2023.07.21 ������
/// </summary>
class TimeManager
{
public:
	static float m_timeScale;

	TimeManager();
	~TimeManager();

	void	Init();
	void	Update();

	int		GetFps()		const { return (int)(m_fps * m_timeScale); }
	float	GetDeltaTime()	const { return m_deltaTime * m_timeScale; }

private:
	float	m_deltaTime;			// 1 ������ �� �ɸ��� �ð� 
	int		m_fps;					// �ʴ� ������ ��

	LARGE_INTEGER m_previousCount;	// ���� frequency ���� �� �� �����ߴ��� �����ϱ� ���� ����
	LARGE_INTEGER m_frequency;		// 1�ʿ� �� �� ���� �ߴ��� �����ϱ� ���� ����

	int		m_accumulationCount;	// 1�� ���� �� �������� ����Ǿ����� ���� ���� ����
	float	m_accumulationTime;		// 1�ʸ� ���� ���� ����
};

