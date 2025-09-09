#pragma once
#include "NPC.h"
//#include "ElementBase.h"
#include <vector>

#include "Vector2.h"

#include <functional>
#include <string>

namespace Graphics { struct Sprite; }
namespace Graphics { class Motion; }
namespace Algorithm { class FindPosition; }
class Transform;
class FSM;
class Animator;
class AudioSource;
namespace Algorithm { class PathFinding; }

struct VectorInt
{
	int x, y;
};

class SkinHeadNPC : public NPC
{
public:
	SkinHeadNPC() {}
	SkinHeadNPC(Transform* npcTransform);
	~SkinHeadNPC();

	enum class State
	{
		Idle,
		Walk,
		Attacked,

		// �������¸� ������
		Interview,
		Credit,
	};

	enum class Direction
	{
		Up,
		Right,
		Down,
		Left,

		Count,
	};

	virtual void Init() override;

	virtual void FixedUpdate() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;

	virtual void PreRender() override;
	virtual void Render(DirectY* directY) override;
	virtual void PostRender(DirectY* directY) override;

	virtual void Release() override;

	virtual ElementType GetElementType() const override;

	virtual GameObject* GetGameObject() const override;
	virtual void SetGameObject(GameObject* gameObject) override;

	void SetPrintLog(std::function<void(std::wstring,bool)> printLog) { m_printLog = printLog; }
	void PrintLog(std::wstring log, bool isNpc);

	MathEngine::Vector2 MoveReverseParabolic(float deltaTime);
	MathEngine::Vector2 MoveParabolic(float deltaTime);
	MathEngine::Vector2 MoveToUI(float deltaTime);
	MathEngine::Vector2 WaitingLinePoint(float x);

	//test
	Graphics::Motion* m_motion;
	int m_index;

	int GetWaitNumber() const { return waitNumber; }
	void SetWaitNumber(int val) { waitNumber = val; }

	bool GetIsAccident() const { return isAccident; }
	void SetIsAccident(bool val) { isAccident = val; }

	bool GetTakeTicket() const { return takeTicket; }
	void SetTakeTicket(bool val) { takeTicket = val; }
	std::vector<MathEngine::Vector2>& GetPaths() { return m_paths; }

	// ���ư��� ���� ����ֱ�
	void MakeReverseTopPos(MathEngine::Vector2 myPos, MathEngine::Vector2 targetPos);
	
	bool GetIsWaiting() const { return isWaiting; }
	void SetIsWaiting(bool val) { isWaiting = val; }

	bool GetIsgoddess() const { return isgoddess; }
	void SetIsgoddess(bool val) { isgoddess = val; }
	bool GetIsInterview() const { return isInterview; }
	void SetIsInterview(bool val) { isInterview = val; }
	bool GetIsInterviewExit() const { return isInterviewExit; }
	void SetIsInterviewExit(bool val) { isInterviewExit = val; }
	void SetIsCreditFly(bool val) { isCreditFly = val; }
	SkinHeadNPC::State GetCurState() const { return m_curState; }
private:
	float m_sumTime;
	float m_degree;
	float m_targetScale;

	float m_time;

	// ��⿭�� ���� ��Ʈ����
	int waitNumber;

	bool takeTicket = false;
	bool isGoingHome = false;
	bool isAccident;
	bool isWaiting = false;
	bool isInterview = false;
	bool isInterviewExit = false;

	bool isCreditFly = false;
	DirectY* m_directY;
	AudioSource* m_audioSource;

	MathEngine::Vector2 m_myPos;
	MathEngine::Vector2 m_topPos;
	MathEngine::Vector2 m_TargetPos;
	MathEngine::Vector2 m_startPos;
	MathEngine::Vector2 m_reverseTopPos;

	std::function<void(std::wstring,bool)> m_printLog;

	// gyu code!
public:
	/// <summary>
	/// ���� �������� ����
	/// </summary>
	void SetNextDestination();

	void SetAudioSource(AudioSource* audioSouce) { m_audioSource = audioSouce; };

private:
	bool IsArrive();
	bool IsAttacked();

	/// <summary>
	/// ���� �������� �� ���� �̵�
	/// </summary>
	void Move(float deltaTime);
	void MoveInUI(float deltaTime);

public:
	void AddPath(MathEngine::Vector2 pos) { GetPaths().push_back(pos); }

	void SetHero(bool val) { m_isHero = val; }
	bool GetHero() { return m_isHero; }
	void ChangeState(State nextState);
private:
	Algorithm::PathFinding* m_pathFind;
	//Graphics::Motion* m_motion;
	Transform* m_transform;

	State m_curState;
	FSM* m_FSM;
	friend class WalkingNPCIdleState;
	friend class WalkingNPCMWalkState;
	friend class WalkingNPCAttackedState;

	/// ������ ����
	// ���� ������
	MathEngine::Vector2 m_currentDestination;
	// ���� ���� �������� ����
	std::vector<MathEngine::Vector2> m_destinations;

	// ���� ���������� ���� ���� ����� �����ǵ�
	std::vector<MathEngine::Vector2> m_paths;
	// ���� ��� �ε���
	int m_pathIndex = 0;

	// ������ ����
	int m_destinationCount;
	// ���� �������� ���� ���� �ʿ��� �ε���
	int m_destinationIndex;
	// �ݴ� �������� ���� ����.
	bool isReverse = false;
	bool m_isHero;

	float m_speed = 200.f;
	MathEngine::Vector2 m_currentDirection = {};
	// �����ġ
	MathEngine::Vector2 m_currentWaitingPoint = {};

public:
	// npc�� ��θ� ���������� ��ȯ�ϱ� ���� �߰�
	void AddPathArr(int posX, int posY) { m_pathArr.push_back({posX, posY}); }

	Animator* GetAnimator() { return m_animator; }
	void SetAnimator(Animator* animator) { m_animator = animator; }

	int GetNpcID() const { return m_npcID; }
	void SetNpcID(int val) { m_npcID = val; }

private:
	void SetNextDirection();
	// ui�ȿ��� ������
	void SetNextDirectionInUI();
	void SetAnimation();

	// npc �ִϸ��̼��� ������ �����ϱ� ���� Direction�� ����.
	Direction m_curDirState = {};
	// npc�� ���� ��ġ�� ������ �������ִ� �迭�� ����
	std::vector<VectorInt> m_pathArr;

	int m_beforePathIndex = 0;

	int m_npcID;
	// �ִϸ��̼�!
	Animator* m_animator = nullptr;

	bool isgoddess;

	/// Gyu code
	// ������ ��ġ�� ���� ���̾ �ٲٱ� ���� �Լ��� ���� ����
	void FindThisPositionAndSetLayer();
	Algorithm::FindPosition* m_findPosition;
	std::vector<std::vector<int>> m_layerArr
		= std::vector<std::vector<int>>(100, std::vector<int>(100));
	int m_tileLayer;
	int m_size;
	int m_currentLayer;
};