#include "SkinHeadNPC.h"
#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "Animator.h"
#include "FSM.h"
#include "WalkingNPCState.h"
#include "FindPosition.h"
#include "../MathEngine/PathFinding.h"
#include "AudioSource.h"

#include <math.h>

SkinHeadNPC::SkinHeadNPC(Transform* npcTransform)
	: m_transform(npcTransform),
	m_motion(nullptr), m_index(0),
	m_sumTime(0), m_degree(0),
	waitNumber(-1),
	m_targetScale(0),
	isAccident(false),
	m_directY(nullptr),
	m_myPos{}, m_topPos{ 1200, 200 }, m_TargetPos{ 1730 - 280, 720 }, m_startPos{}
	, m_curState{}
	, m_FSM(nullptr)
	, m_currentDestination{}
	, m_paths{}
	, m_pathIndex(0)
	, m_destinationCount(0)
	, m_destinationIndex(0)
	, isReverse(false)
	, m_speed(200.f)
	, m_currentDirection{}
	, m_isHero(false)
	, m_time(0)
	, m_audioSource(nullptr)
	, m_tileLayer(0)
	, m_size(60)
	, m_currentLayer(0)
{
	m_FSM = new FSM(new WalkingNPCIdleState(this));
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

SkinHeadNPC::~SkinHeadNPC()
{
	int a = 3;
	//delete m_motion;

	delete m_FSM;
	delete m_findPosition;
}

void SkinHeadNPC::Init()
{
	m_animator->SetCurrentMotion("_front_left_walking");
	m_audioSource = (AudioSource*)(m_gameObject->GetElement(ElementType::AudioSource));

	if (GetCurState() == State::Credit) return;
	m_transform->SetLocalScale({ 0.5f,0.5f });
}

void SkinHeadNPC::FixedUpdate()
{
}

void SkinHeadNPC::Update(float deltaTime)
{
	if (GetCurState() == State::Credit)
	{
		m_TargetPos = { 1900, 600 };
		m_topPos = { 1500, -100 };
		m_myPos = m_transform->GetLocalPosition();
		
		//m_transform->SetTransform(m_directY);

		if (isCreditFly)
		{
			m_startPos = m_myPos;
			isCreditFly = false;
		}

		m_transform->SetLocalPosition(MoveParabolic(deltaTime));

		m_degree += deltaTime * 10;
		if (m_degree > 360)
		{
			m_degree = 0;
		}

		m_transform->Rotate(m_degree);

		/// ������ �����Ϻ�ȭ
		// m_topPos.x������ �������� ������
		if (m_myPos.x <= m_topPos.x)
		{
			float midScale = 1.f + 0.5f - (((m_topPos.x - m_myPos.x) / (m_topPos.x - m_startPos.x)) / 2.f);
			m_transform->SetLocalScale({ midScale,midScale });
		}
	}

	if (m_curState == State::Credit)
	{
		return;
	}

	m_time += deltaTime;
	if (m_time > 1)
	{
		m_index++;

		if (m_index >= 3)
		{
			m_index = 0;
		}

		m_time = 0;
	}

	// ���� ġ������ �����ϴ� ��
	m_TargetPos = WaitingLinePoint((float)(1650.f - (180.f / 3) * 3));
	
	// ī�޶� ������� ���� ��ġ�� �����ϱ� ���Ѻ���
	D2D1_MATRIX_3X2_F accidentMatrix = m_transform->GetTransformMatrix() * CameraManager::GetInstance().GetCameraMatrix();
	Collider* myCollider = ((Collider*)(m_gameObject->GetElement(ElementType::Collider)));

	/// �浹���� ���
	if (myCollider->GetIsCollision() && isGoingHome == false && isAccident == false/* && isInterviewExit==false*/)
	{
		m_audioSource->PlayBack("sfx_hit_npc_1");
		// �浹���¿� ����.
		SetIsAccident(true);
		
		// ī�޶� ������� �ʰ�
		m_transform->SetUseCamera(false);

		// ������ġ�� 0���� �ű��.
		m_transform->SetLocalPosition({ 0,0 });

		// ī�޶� ������� ��ġ�� ��� ���� ��ġ�� ��ġ ��Ų��.
		m_myPos = m_directY->MarixToVector(accidentMatrix, m_transform->GetLocalPosition());

		/// �浹�� ���۵Ǹ� ��ŸƮ ��� �����Ѵ�.
		m_startPos = m_myPos;

		// ī�޶����� �Ŀ� ���� ��ġ�� ���� �� �ֵ��� �������� �ű��.
		m_transform->SetLocalPosition(m_myPos);

		// ���̾ ������ ȭ��� ���� ���� ǥ�õǵ��� �ű��.
		m_transform->SetLayer(400);
	}

	/// �̵�
	// �浹���¶�� && ������ x������� && ������ ���ư��°� �ƴҰ��
	// ui�޴� ����(Ÿ������)���� �̵��Ѵ�.
	if (GetIsAccident() && (m_myPos.x <= m_TargetPos.x) && !isGoingHome)
	{
		// ���������� �����δ�.
		m_transform->SetLocalPosition(MoveParabolic(deltaTime));
		m_myPos = m_transform->GetLocalPosition();
	}
	/// ������ ���ư��� �ϴ°��
	else if (isGoingHome == true && ((int)(m_myPos.x*100)/1000 != (int)(m_paths[0].x*100)/1000))
	{
		// ���������� �����δ�.
		m_transform->SetLocalPosition(MoveReverseParabolic(deltaTime));
		m_myPos = m_transform->GetLocalPosition();
		m_transform->Rotate(m_myPos.x);
	}
	else if(isGoingHome)
	{
		m_transform->SetLocalPosition(m_paths[0]);
		m_transform->SetLocalRotation(0);
		isGoingHome = false;
		ChangeState(State::Idle);
		m_transform->SetLayer(5);

		/// Ƽ���� �ʱ�ȭ�ϰ� �޴� ��ġ�� �ٽ� �����غ���
		SetWaitNumber(-1);
		isAccident = false;
		isInterview = false;
	}

	switch (GetCurState())
	{
	case SkinHeadNPC::State::Idle:
		// ���ο� ���� ã�� Walk�� ����!
		// �̷��� �ϴ°� �´����� �𸣰����� WalkingNPCState���� SetNextDestination���� �ٲٱ�� ��.
		// �ƴ� ����
		SetNextDestination();
		//PathFind();
		ChangeState(State::Walk);
		break;

	case SkinHeadNPC::State::Walk:
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
	case SkinHeadNPC::State::Attacked:
		// ���� �΋H���� ������ UI�� ����������!
		break;
	case SkinHeadNPC::State::Interview:
		// ����ȣ 1~4f�� �ް�
		// ui�� �����ϸ� ���ͺ� �����°� �˴ϴ�! 

		ChangeState(State::Interview);
		break;
	case SkinHeadNPC::State::Credit:

		break;
	default:
		break;
	}
	m_FSM->UpdateState(deltaTime);

	/*--------------------------------------------------------------------------------------*/
	if (isWaiting)
	{
		isInterview = true;

		switch (waitNumber)
		{
		case (1):
			m_currentWaitingPoint = WaitingLinePoint(1650.f);
			break;
		case (2):
			m_currentWaitingPoint = WaitingLinePoint((float)(1650.f - (180.f / 3)));
			break;
		case (3):
			m_currentWaitingPoint = WaitingLinePoint((float)(1650.f - (180.f / 3) * 2));
			break;
		default:
			m_currentWaitingPoint = WaitingLinePoint((float)(1650.f - (180.f / 3) * 3));
			break;
		}

		m_transform->SetLocalPosition(m_currentWaitingPoint);
		m_curDirState = Direction::Up;
		SetAnimation();
	}
	/*--------------------------------------------------------------------------------------*/

	// ������ �������
	if (isInterview && waitNumber == -1&& !m_isHero)
	{
		waitNumber = 5;
		//m_gameObject->SetIsDraw(true);
		isInterview = false;
		isAccident = true;
	}
	if (isInterview && waitNumber == -1 && m_isHero)
 	{
  		//m_transform->SetLocalScale({ 2.f,2.f });
  		m_gameObject->SetActive(false);
 		//waitNumber = 5;
  		//isInterview = false;
 		//isAccident = true;
 	}

	// ȸ���� ����
	// ȸ���� �浹���� + m_myPos.x�� 1500 �����϶� 
	// ȸ�������� 360 or 0 �� �ƴ� �� ���� �Ѵ�
	if (GetIsAccident())
	{
		// ������ ��� �������ش�.
		m_degree += deltaTime * 10;
		if (m_degree > 360)
		{
			m_degree = 0;
		}

		/// ������ �����Ϻ�ȭ
		// m_topPos.x������ �������� ������
		if (m_myPos.x <= m_topPos.x)
		{
			float midScale = 1.f + 0.5f - (((m_topPos.x - m_myPos.x) / (m_topPos.x - m_startPos.x)) / 2.f);
			m_transform->SetLocalScale({midScale,midScale});
		}
		// m_topPos.x - m_TargetPos.x������ �������� ������
		else if (m_myPos.x > m_topPos.x)
		{
			float endScale = 1.f + 0.5f - (1.f - (m_TargetPos.x - m_myPos.x) / (m_TargetPos.x - m_topPos.x));
			m_transform->SetLocalScale({endScale,endScale});
		}

		// x���� ��ǥ������ �����ϸ� ȸ���� �����.
		// ��ǥ���������� �������� �����Ѵ�.
		if ((m_myPos.x >= m_TargetPos.x /*&& isInterviewExit != true*/)/*&&isWaiting*/)
		{
			SetIsAccident(false);
			m_degree = 0; 
			m_transform->SetLocalRotation(0);
			m_transform->SetLocalScale({0.5f,0.5f});
			
			// ���ǥ�� �޴´�.
			if (waitNumber == -1)
			{
				isWaiting = true;
				SetTakeTicket(true);
			}
		}

		// ��⿭���� ����� �����ڸ��� ���ư���.
		if ((isAccident==false) && (waitNumber == 5) && m_startPos.x < m_myPos.x)
		{
			// ī�޶� ���
			m_transform->SetUseCamera(true);
			// ī�޶��Ʈ���� ��ŭ ���ֱ�
			m_myPos = m_transform->GetLocalPosition() - CameraManager::GetInstance().GetCameraPosition();
			// ī�޶� ��������� ������ġ�� ����
			m_transform->SetLocalPosition(m_myPos);

			m_transform->SetLocalScale({0.5,0.5});
			MakeReverseTopPos(m_myPos, m_paths[0]);
			
			//pathIndex�� �ٲ���� �����ؼ� �� ������
			m_pathIndex = 0;
			isGoingHome = true;
			isAccident = false;
			isWaiting = false;
			//isInterview = false;

			isInterviewExit = false;
		}

		m_transform->Rotate(m_degree);
	}

}

void SkinHeadNPC::LateUpdate()
{
}

void SkinHeadNPC::PreRender()
{
	switch (GetCurState())
	{
	case State::Idle:
		break;
	case State::Walk:
		FindThisPositionAndSetLayer();
		break;
	case State::Attacked:
		break;
	case State::Interview:
		m_transform->SetLayer(100000);
		break;
	default:
		break;

	}
}

void SkinHeadNPC::Render(DirectY* directY)
{
	m_directY = directY;
}

void SkinHeadNPC::PostRender(DirectY* directY)
{
}

void SkinHeadNPC::Release()
{
}

ElementType SkinHeadNPC::GetElementType() const
{
	return ElementType::Script;
}

GameObject* SkinHeadNPC::GetGameObject() const
{
	return m_gameObject;
}

void SkinHeadNPC::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}



void SkinHeadNPC::PrintLog(std::wstring log, bool isNpc)
{
	m_printLog(log,isNpc);
}

/// <summary>
/// �������̵��� ���� �Լ�
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
MathEngine::Vector2 SkinHeadNPC::MoveParabolic(float deltaTime)
{
	float A = (float)(m_TargetPos.y * (pow(m_myPos.x, 2) - pow(m_topPos.x, 2))
		+ m_topPos.y * (pow(m_TargetPos.x, 2) - pow(m_myPos.x, 2))
		+ m_myPos.y * (pow(m_topPos.x, 2) - pow(m_TargetPos.x, 2)))
		/ (2 * ((m_TargetPos.y - m_topPos.y) * m_myPos.x
			+ (m_myPos.y - m_TargetPos.y) * m_topPos.x
			+ (m_topPos.y - m_myPos.y) * m_TargetPos.x));
	
	float C = (float)(m_myPos.y - m_topPos.y) / (float)((pow(m_myPos.x, 2) - pow(m_topPos.x, 2) + 2 * A * (m_topPos.x - m_myPos.x)));
	
	float B = m_topPos.y - (float)(C * pow((m_topPos.x - A),2));

	m_myPos.x += deltaTime* 200;

	float y = (float)(C * pow((m_myPos.x - A), 2) + B);


	return { m_myPos.x,y };
}
/// <summary>
/// ���ڸ��� ���ư��� �Լ�
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
MathEngine::Vector2 SkinHeadNPC::MoveReverseParabolic(float deltaTime)
{
	float A = (float)(m_paths[0].y * (pow(m_myPos.x, 2) - pow(m_reverseTopPos.x, 2))
		+ m_reverseTopPos.y * (pow(m_paths[0].x, 2) - pow(m_myPos.x, 2))
		+ m_myPos.y * (pow(m_reverseTopPos.x, 2) - pow(m_paths[0].x, 2)))
		/ (2 * ((m_paths[0].y - m_reverseTopPos.y) * m_myPos.x
			+ (m_myPos.y - m_paths[0].y) * m_reverseTopPos.x
			+ (m_reverseTopPos.y - m_myPos.y) * m_paths[0].x));

	float C = (float)(m_myPos.y - m_reverseTopPos.y) / (float)((pow(m_myPos.x, 2) - pow(m_reverseTopPos.x, 2) + 2 * A * (m_reverseTopPos.x - m_myPos.x)));

	float B = m_reverseTopPos.y - (float)(C * pow((m_reverseTopPos.x - A), 2));

	if(m_myPos.x >= m_paths[0].x)
	{
		m_myPos.x -= deltaTime * 200;
	}
	else if (m_myPos.x < m_paths[0].x)
	{
		m_myPos.x += deltaTime * 200;
	}

	float y = (float)(C * pow((m_myPos.x - A), 2) + B);


	return { m_myPos.x, y };
}

MathEngine::Vector2 SkinHeadNPC::MoveToUI(float deltaTime)
{
	const int intensity = 600;
	// �ð��� ���������� x���� �����Ѵ�.
	float a = (m_TargetPos.y - m_myPos.y) / (m_TargetPos.x - m_myPos.x);
	m_myPos += deltaTime;

	return { 1 * deltaTime * intensity, a * deltaTime * intensity };
}

MathEngine::Vector2 SkinHeadNPC::WaitingLinePoint(float x)
{
	float y = -0.604f * x + 1795.f;
	return { x,y };
}

/// <summary>
/// ���ư��� �������� �߰������� ����� �Լ�
/// </summary>
/// <param name="myPos">������</param>
/// <param name="targetPos">������</param>
void SkinHeadNPC::MakeReverseTopPos(MathEngine::Vector2 myPos, MathEngine::Vector2 targetPos)
{
	if (myPos.x >= targetPos.x)
	{
		m_reverseTopPos.x = targetPos.x + (myPos.x - targetPos.x)/2;
	}
	else if (myPos.x < targetPos.x)
	{
		m_reverseTopPos.x = myPos.x + (targetPos.x - myPos.x)/2;
	}

	if (myPos.y >= targetPos.y)
	{
		m_reverseTopPos.y = targetPos.y - 500;
	}
	else if (myPos.y < targetPos.y)
	{
		m_reverseTopPos.y = targetPos.y - 500;
	}
}

void SkinHeadNPC::SetNextDestination()
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
		m_pathIndex--;
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
	SetAnimation();
}

bool SkinHeadNPC::IsArrive()
{
	// TODO : ���� �����ߴ����� �˻�!
	// ���������� �� ũ�� ��µ� �̰� �´��� �𸣰ڴ�. ��� �ɾ���� ���� ���������� ���� �� ����. 
	Vector2 currentPos = m_transform->GetLocalPosition();
	if (m_currentDestination.x + 10.f >= currentPos.x
		&& m_currentDestination.x - 10.f <= currentPos.x
		&& m_currentDestination.y + 10.f >= currentPos.y
		&& m_currentDestination.y - 10.f <= currentPos.y)
	{
		//m_transform->SetLocalPosition(m_currentDestination);
		return true;
	}

	return false;
}

bool SkinHeadNPC::IsAttacked()
{
	// TODO : ���� ġ�������� �˻�!
	return isAccident;
}

void SkinHeadNPC::Move(float deltaTime)
{
	m_transform->Translate(m_currentDirection * m_speed * deltaTime);
}

void SkinHeadNPC::MoveInUI(float deltaTime)
{
	m_transform->Translate(m_currentWaitingPoint * m_speed * deltaTime);
}

void SkinHeadNPC::ChangeState(State nextState)
{
	m_curState = nextState;
	switch (GetCurState())
	{
	case SkinHeadNPC::State::Idle:
		m_FSM->ChangeState(new WalkingNPCIdleState(this));
		break;
	case SkinHeadNPC::State::Walk:
		m_FSM->ChangeState(new WalkingNPCWalkState(this));
		break;
	case SkinHeadNPC::State::Attacked:
		m_FSM->ChangeState(new WalkingNPCAttackedState(this));
		break;
	case SkinHeadNPC::State::Interview:
		//m_FSM->ChangeState(new WalkingNPCAttackedState(this));
		break;
	case SkinHeadNPC::State::Credit:
		//m_FSM->ChangeState(new WalkingNPCAttackedState(this));
		break;
	default:
		break;
	}
}

void SkinHeadNPC::SetNextDirection()
{
	VectorInt currentPos = m_pathArr[m_beforePathIndex];
	VectorInt nextPos = m_pathArr[m_pathIndex];

	if (currentPos.x == nextPos.x)
	{
		if (currentPos.y <= nextPos.y)
		{
			m_curDirState = Direction::Down;
		}
		else
		{
			m_curDirState = Direction::Up;
		}
	}
	else if (currentPos.y == nextPos.y)
	{
		if (currentPos.x <= nextPos.x)
		{
			m_curDirState = Direction::Right;
		}
		else
		{
			m_curDirState = Direction::Left;
		}
	}
	else
	{
		m_curDirState;
	}
}

void SkinHeadNPC::SetNextDirectionInUI()
{
	if (m_myPos.x == m_currentWaitingPoint.x)
	{
		if (m_myPos.y <= m_currentWaitingPoint.y)
		{
			m_curDirState = Direction::Down;
		}
		else
		{
			m_curDirState = Direction::Up;
		}
	}
	else if (m_myPos.y == m_currentWaitingPoint.y)
	{
		if (m_myPos.x <= m_currentWaitingPoint.x)
		{
			m_curDirState = Direction::Right;
		}
		else
		{
			m_curDirState = Direction::Left;
		}
	}
	else
	{
		m_curDirState;
	}
}

void SkinHeadNPC::SetAnimation()
{
	switch (m_curDirState)
	{
	case Direction::Up:
		m_animator->SetCurrentMotion("_back_right_walking");
		break;
	case Direction::Right:
		m_animator->SetCurrentMotion("_front_right_walking");
		break;
	case Direction::Down:
		m_animator->SetCurrentMotion("_front_left_walking");
		break;
	case Direction::Left:
		m_animator->SetCurrentMotion("_back_left_walking");
		break;
	default:
		break;
	}
}

void SkinHeadNPC::FindThisPositionAndSetLayer()
{
	// �迭 ��ǥ, ������ ��ġ
	std::pair<MathEngine::Vector2, MathEngine::Vector2> getData
		= m_findPosition->FindNearest(m_transform->GetLocalPosition());

	m_currentLayer = m_layerArr[getData.first.x][getData.first.y];

	// ���⼭ ���̾� ����
	m_transform->SetLayer(m_currentLayer + 1);
}
