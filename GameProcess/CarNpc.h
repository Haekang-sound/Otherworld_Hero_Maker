#pragma once
#include "NPC.h"
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

struct CarVectorInt
{
	int x, y;
};

class Transform;
class CarNpc : public NPC
{
public:
	CarNpc(Transform* transform);
	virtual ~CarNpc();
	enum class State
	{
		Idle,
		Move,
		Attacked,
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

	std::vector<MathEngine::Vector2>& GetPaths() { return m_paths; }

private:
	DirectY* m_directY;

	// gyu code!
public:
	/// <summary>
	/// ���� �������� ����
	/// </summary>
	void SetNextDestination();

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

private:
	void ChangeState(State nextState);

	//Graphics::Motion* m_motion;
	Transform* m_transform;

	State m_curState;
	FSM* m_FSM;
	friend class CarNPCIdleState;
	friend class CarNPCMoveState;
	friend class CarNPCAttackedState;

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
	void AddPathArr(int posX, int posY) { m_pathArr.push_back({ posX, posY }); }

	int GetCarID() const { return m_carID; }
	void SetCarID(int val) { m_carID = val; }

private:
	void SetNextDirection();

	// npc �ִϸ��̼��� ������ �����ϱ� ���� Direction�� ����.
	Direction m_curDirState = {};
	// npc�� ���� ��ġ�� ������ �������ִ� �迭�� ����
	std::vector<CarVectorInt> m_pathArr;

	int m_beforePathIndex = 0;
	int m_carID;

public:
	void SetMotion(Graphics::Motion* motion) { m_motion = motion; }
private:
	int m_npcId;

	// ���
	Graphics::Motion* m_motion;
	int m_spriteIndex;

	MathEngine::Vector2 m_preDirection;
	MathEngine::Vector2 m_direction;

	float m_time = 0.f;

	// ���̾� ã��
		// ������ ��ġ�� ���� ���̾ �ٲٱ� ���� �Լ��� ���� ����
	void FindThisPositionAndSetLayer();
	Algorithm::FindPosition* m_findPosition;
	std::vector<std::vector<int>> m_layerArr
		= std::vector<std::vector<int>>(100, std::vector<int>(100));
	int m_tileLayer;
	int m_size;
	int m_currentLayer;
};

