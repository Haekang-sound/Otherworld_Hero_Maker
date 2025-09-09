
#include "WalkingNPC.h"
#include "FSM.h"
#include "WalkingNPCState.h"


#include "../MathEngine/PathFinding.h"

#include "Transform.h"
WalkingNPC::WalkingNPC(Transform* npcTransform)
	:m_pathFind(nullptr)
	, m_currentDestination()
	, m_destinations{}
	, m_destinationCount(0)
	, m_destinationIndex(0)
	, m_transform(npcTransform)
{
	Init();

}

WalkingNPC::~WalkingNPC()
{
	delete m_FSM;
	delete m_motion;
	delete m_pathFind;
}

void WalkingNPC::Init()
{
	m_pathFind = new Algorithm::PathFinding();
	m_FSM = new FSM(new WalkingNPCIdleState(this));
	
	// Idle�� �� ù ������ ����
	m_curState = State::Idle;
	// Idle ����
	ChangeState(State::Idle);

	// �� �б�
	m_pathFind->ReadSource("Text/Map/Stage1_check.txt");


	// ���� ��ġ�� ������ �缳��
	//m_pathFind->SetSatrtNode(m_transform->GetLocalPosition());
	//m_pathFind->SetEndNode(m_destinations[0]);

	// ���� ��η� �̵�
	// m_pathFind->nearestLocation();
	// ��� Ž��
	//m_pathFind->SolveAstar();

	// ���� ��� ������Ʈ
	//m_pathFind->nearestLocation();
	//m_pathFind->GetFinalPath();

}

void WalkingNPC::FixedUpdate()
{

}

void WalkingNPC::Update(float deltaTime)
{
	switch (m_curState)
	{
	case WalkingNPC::State::Idle:
		// ���ο� ���� ã�� Walk�� ����!
		// �̷��� �ϴ°� �´����� �𸣰����� WalkingNPCState���� SetNextDestination���� �ٲٱ�� ��.
		// �ƴ� ����
		SetNextDestination();
		PathFind();
		ChangeState(State::Walk);
		break;

	case WalkingNPC::State::Walk:
		// ���� �ε����� ��� 
		if (IsAttacked())
		{
			ChangeState(State::Attacked);
			break;
		}

		// �������� ���
		if (IsArrive())
		{
			ChangeState(State::Idle);
			break;
		}

		// �ƹ��͵� �ƴ� ��� ��� �̵�
		// Move();

		break;
	case WalkingNPC::State::Attacked:
		// ���� �΋H���� ������ UI�� ����������!
		
		break;
	default:
		break;
	}
	m_FSM->UpdateState();
}

void WalkingNPC::LateUpdate()
{
}

void WalkingNPC::PreRender()
{
}

void WalkingNPC::Render(DirectY* directY)
{
	directY->DrawBitmap(m_motion->GetSprite(0));
}

void WalkingNPC::PostRender(DirectY* directY)
{
}

void WalkingNPC::Release()
{
}

ElementType WalkingNPC::GetElementType() const
{
	return ElementType::Script;
}

GameObject* WalkingNPC::GetGameObject() const
{
	return m_gameObject;
}

void WalkingNPC::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}


void WalkingNPC::SetNextDestination()
{
// 	m_currentDestination = m_destinations[m_destinationIndex];
// 	m_destinationIndex++;
// 	m_destinationIndex %= m_destinationCount;
}

void WalkingNPC::PathFind()
{
	return;
	// path find start

	m_currentDestination;	// ������

	m_pathFind->SetSatrtNode(m_transform->GetLocalPosition());
	m_pathFind->SetEndNode(m_destinations[0]);

}

bool WalkingNPC::IsArrive()
{
	// ���� �ߴ��� ���� Ȯ��
	return false;
}

bool WalkingNPC::IsAttacked()
{
	// ���� ġ������ ���� Ȯ��
	return false;
}

void WalkingNPC::Walk()
{
	//m_pathFind->nearestLocation();
}

void WalkingNPC::ChangeState(State nextState)
{
	m_curState = nextState;
	switch (m_curState)
	{
	case WalkingNPC::State::Idle:
		m_FSM->ChangeState(new WalkingNPCIdleState(this));
		break;
	case WalkingNPC::State::Walk:
		m_FSM->ChangeState(new WalkingNPCWalkState(this));
		break;
	case WalkingNPC::State::Attacked:
		m_FSM->ChangeState(new WalkingNPCAttackedState(this));
		break;
	default:
		break;
	}
}
