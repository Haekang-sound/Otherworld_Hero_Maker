#include "CarNpc.h"
#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "Animator.h"
#include "FSM.h"
//#include "WalkingNPCState.h"
#include "CarNPCState.h"

#include "../MathEngine/PathFinding.h"
#include "Vector2.h"
#include <math.h>
#include "MotionAnimator.h"
#include "FindPosition.h"

CarNpc::CarNpc(Transform* transform)
	:m_transform(transform)
	, m_preDirection({ -1.f,-1.f })
	, m_direction({0.f, 0.f})
	, m_spriteIndex(0)
	, m_tileLayer(0)
	, m_size(60)
	, m_currentLayer(0)
{
	m_FSM = new FSM(new CarNPCIdleState(this));
	m_findPosition = new Algorithm::FindPosition();
	// ù ��μ���
	m_pathIndex = 0;
	// Idle�� �� ù ������ ����
	m_curState = State::Idle;
	// Idle ����
	ChangeState(State::Idle);


	// ���̾� �ʱ�ȭ
	m_findPosition->Init();
	MathEngine::Vector2 renderPos(0, 0);
	int prevY = 0;
	int prevX = 0;
	while (true)
	{
		int y = static_cast<int>(renderPos.y);
		int x = static_cast<int>(renderPos.x);

		if (renderPos.x == 0)
		{
			// Ÿ�� ���̾� ����
			m_tileLayer++;
		}

		if (renderPos.y == m_size - 1)
		{
			m_tileLayer++;
		}
		m_layerArr[y][x] = m_tileLayer;

		if (renderPos.x == m_size - 1 && renderPos.y == m_size - 1)
		{
			break;
		}

		if (renderPos.x == m_size - 1)
		{
			prevX++;
			renderPos.x = static_cast<float>(prevX);
			renderPos.y = static_cast<float>(prevY);
		}
		else if (renderPos.y == 0)
		{
			prevY++;
			renderPos.y = static_cast<float>(prevY);
			renderPos.x = 0;
		}
		else
		{
			renderPos.y -= 1;
			renderPos.x += 1;
		}

		if (renderPos.y > m_size - 1)
			renderPos.y--;
		if (renderPos.x > m_size - 1)
			renderPos.x--;
	}
}

CarNpc::~CarNpc()
{
	delete m_FSM;
	delete m_motion;
	delete m_findPosition;
}

void CarNpc::Init()
{
	//m_animator->SetCurrentMotion("_back_right_walking");
}

void CarNpc::FixedUpdate()
{

}

void CarNpc::Update(float deltaTime)
{
	switch (m_curState)
	{
	case CarNpc::State::Idle:
		// ���ο� ���� ã�� Walk�� ����!
		// �̷��� �ϴ°� �´����� �𸣰����� WalkingNPCState���� SetNextDestination���� �ٲٱ�� ��.
		// �ƴ� ����
		SetNextDestination();
		//PathFind();
		ChangeState(State::Move);
		break;

	case CarNpc::State::Move:
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
			//SetNextDestinationTestVer();
			break;
		}

		// �ƹ��͵� �ƴ� ��� ��� �̵�
		Move(deltaTime);
		m_gameObject;
		break;
	case CarNpc::State::Attacked:
		// ���� �΋H���� ������ UI�� ����������!
		break;
	default:
		break;
	}
	m_FSM->UpdateState(deltaTime);


	/// ��������Ʈ �ε��� ����

	m_time += deltaTime;

	if (m_time > 0.03f)
	{
		m_time = 0;

		// �ε��� ����
		if ((m_preDirection.x * m_direction.x < 0.f) || (m_preDirection.y * m_direction.y < 0.f))
		{
			float crossProduct = m_preDirection.Cross(m_direction);
			// ��ȸ��
			if (crossProduct >= 0.f)
			{
				m_spriteIndex++;
			}
			// ��ȸ��
			else if (crossProduct < 0.f)
			{
				m_spriteIndex--;
			}
		}
	}

	// �ε��� ����
	if (m_spriteIndex < 0)
	{
		m_spriteIndex += 29;
	}

	m_spriteIndex %= 30;

	// ���� ���� ����
	if (m_direction.x > 0.f && m_direction.y > 0.f && m_spriteIndex == 4 ||
		m_direction.x < 0.f && m_direction.y > 0.f && m_spriteIndex == 11 || 
		m_direction.x < 0.f && m_direction.y < 0.f && m_spriteIndex == 18 ||
		m_direction.x > 0.f && m_direction.y < 0.f && m_spriteIndex == 26)
	{
		m_preDirection = m_direction;
	}
}

void CarNpc::LateUpdate()
{

}

void CarNpc::PreRender()
{
	FindThisPositionAndSetLayer();
}

void CarNpc::Render(DirectY* directY)
{
	m_directY = directY;
	directY->DrawBitmap(m_motion->GetSprite(m_spriteIndex));
}

void CarNpc::PostRender(DirectY* directY)
{

}

void CarNpc::Release()
{

}

ElementType CarNpc::GetElementType() const
{
	return ElementType::Script;
}

GameObject* CarNpc::GetGameObject() const
{
	return m_gameObject;
}

void CarNpc::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

void CarNpc::SetNextDestination()
{
	m_beforePathIndex = m_pathIndex;

	m_transform->SetLocalPosition(m_paths[m_pathIndex]);
	// ���� ��� ����
	if (!isReverse)
	{
		m_pathIndex++;
	}
	else
	{
		m_pathIndex--;
	}

	if (m_pathIndex >= static_cast<int>(GetPaths().size()))
	{
		isReverse = true;
		//m_pathIndex--;
		m_pathIndex-=2;
	}
	if (m_pathIndex < 0)
	{
		isReverse = false;
		m_pathIndex = 0;
	}
	m_currentDestination = GetPaths()[m_pathIndex];

	MathEngine::Vector2 currentPos(m_transform->GetTransformMatrix().dx, m_transform->GetTransformMatrix().dy);
	// �̵�
	m_currentDirection = GetPaths()[m_pathIndex] - currentPos;
	m_currentDirection = m_currentDirection.Normalize();

	// npc�� ���� ����
	SetNextDirection();
}

bool CarNpc::IsArrive()
{
	// TODO : ���� �����ߴ����� �˻�!
	Vector2 currentPos = m_transform->GetLocalPosition();
	if (m_currentDestination.x + 10.f >= currentPos.x
		&& m_currentDestination.x - 10.f <= currentPos.x
		&& m_currentDestination.y + 10.f >= currentPos.y
		&& m_currentDestination.y - 10.f <= currentPos.y)
	{
		// m_transform->SetLocalPosition(m_currentDestination);
		return true;
	}

	return false;
}

bool CarNpc::IsAttacked()
{
	// TODO : ���� ġ�������� �˻�!
	//return isAccident;

	// �̰� ����
	return false;
}

void CarNpc::Move(float deltaTime)
{
	m_transform->Translate(m_currentDirection * m_speed * deltaTime);
}

void CarNpc::MoveInUI(float deltaTime)
{

}

void CarNpc::ChangeState(State nextState)
{
	m_curState = nextState;
	switch (m_curState)
	{
	case CarNpc::State::Idle:
		m_FSM->ChangeState(new CarNPCIdleState(this));
		break;
	case CarNpc::State::Move:
		m_FSM->ChangeState(new CarNPCMoveState(this));
		break;
	case CarNpc::State::Attacked:
		m_FSM->ChangeState(new CarNPCAttackedState(this));
		break;
	default:
		break;
	}
}

void CarNpc::SetNextDirection()
{
	CarVectorInt currentPos = m_pathArr[m_beforePathIndex];
	CarVectorInt nextPos = m_pathArr[m_pathIndex];

	// �̰Ŵ� �ڵ��� �ִϸ��̼��� ����� ���� ���� , �׸��� �� �Ʒ��� ȸ���ϱ� ���� ��ġ
	//m_preDirection.x = (float)m_pathArr[m_beforePathIndex].x;
	//m_preDirection.y = (float)m_pathArr[m_beforePathIndex].y;
	//// �������


	//// �̰Ŵ� �ڵ��� �ִϸ��̼��� ����� ���� ���� , �׸��� �� �Ʒ��� ȸ���� ���� ��ġ
	//m_direction.x = (float)m_pathArr[m_pathIndex].x;
	//m_direction.y = (float)m_pathArr[m_pathIndex].y;
	// �������


	Vector2 direction = m_paths[m_pathIndex] - m_paths[m_beforePathIndex] ;
	direction.Normalize();
	m_direction = direction;


	//if (currentPos.x == nextPos.x)
	//{
	//	if (currentPos.y <= nextPos.y)
	//	{
	//		m_curDirState = Direction::Down;
	//	}
	//	else
	//	{
	//		m_curDirState = Direction::Up;
	//	}
	//}
	//else if (currentPos.y == nextPos.y)
	//{
	//	if (currentPos.x <= nextPos.x)
	//	{
	//		m_curDirState = Direction::Right;
	//	}
	//	else
	//	{
	//		m_curDirState = Direction::Left;
	//	}
	//}
	//else
	//{
	//	m_curDirState;
	//}
}

void CarNpc::FindThisPositionAndSetLayer()
{
	// �迭 ��ǥ, ������ ��ġ
	std::pair<MathEngine::Vector2, MathEngine::Vector2> getData
		= m_findPosition->FindNearest(m_transform->GetLocalPosition());

	m_currentLayer = m_layerArr[getData.first.x][getData.first.y];

	// ���⼭ ���̾� ����
	m_transform->SetLayer(m_currentLayer + 1);
}
