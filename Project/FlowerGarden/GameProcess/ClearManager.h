#pragma once
#include "Singleton.h"
#include "../DirectY/Sprite.h"

class DirectY;

class ClearManager : public Singleton<ClearManager>
{
public:
	void SetClearStage(int clearStageNum) 
	{ 
		if (clearStageNum > m_clearStageNum || clearStageNum == 0)
		{
			m_clearStageNum = clearStageNum; 
		}
	};
	int GetClearStage() { return m_clearStageNum; }

	bool CheckClear() const { return m_GameClear; }
	bool CheckDead() const { return m_isDead; }
	void SetClear(bool isclear) { m_GameClear = isclear; }
	bool GetClear() { return m_GameClear; }
	bool SetDead(bool isdead) { return m_isDead = isdead; }

	void Update(float deltaTime);

private:
	int m_clearStageNum;

	// �� ���� Ŭ������� ���� �����Ϸ��� �����ڸ� ���ܾ� �Ѵ�.
	ClearManager() : m_clearStageNum(0) {}
	~ClearManager() {}

	friend class Singleton<ClearManager>;
	bool m_GameClear = false;
	bool m_isDead = false;
};