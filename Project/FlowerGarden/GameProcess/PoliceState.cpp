#include "PoliceState.h"
#include "Police.h"

#include "AudioSource.h"
#include "Transform.h"
#include "Vector2.h"
#include "../MathEngine/FindPosition.h"
#include "../MathEngine/PathFinding.h"
#include "GameObject.h"

#include "CameraManager.h"
#include "Player.h"

#pragma region IdleState

PoliceIdleState::PoliceIdleState(NPC* npc) 
	: BaseState(npc)
	, m_route()
	, m_index(0)
{
	Police* police = (Police*)m_NPC;
	m_route = police->m_route;

}

PoliceIdleState::~PoliceIdleState()
{

}

void PoliceIdleState::OnStateEnter()
{
	Police* police = (Police*)m_NPC;
	Transform* policeTransform = (Transform*)(police->GetGameObject()->GetElement(ElementType::Transform));

	// ���� ��ġ
	MathEngine::Vector2 location = policeTransform->GetLocalPosition() + MathEngine::Vector2(80.f, 90.f);
	std::pair<MathEngine::Vector2, MathEngine::Vector2>
		policePos = police->m_pathfind->m_findPotition->FindNearest(location);
	police->m_pathfind->SetStartNode((int)policePos.first.x, (int)policePos.first.y);

	float min = FLT_MAX;
	for (int i = 0; i < (int)m_route.size(); i++)
	{
		float distance = m_route[i].Distance(policePos.first);
		if (distance < min)
		{
			min = distance;
			m_index = i;
		}
	}
}

void PoliceIdleState::OnStateUpdate(float deltaTime)
{
	Police* police = (Police*)m_NPC;
	Transform* policeTransform = (Transform*)(police->GetGameObject()->GetElement(ElementType::Transform));
	
	// ���� ��ġ
	MathEngine::Vector2 location = policeTransform->GetLocalPosition() + MathEngine::Vector2(80.f, 90.f);
	std::pair<MathEngine::Vector2, MathEngine::Vector2>
		policePos = police->m_pathfind->m_findPotition->FindNearest(location);
	police->m_pathfind->SetStartNode((int)policePos.first.x, (int)policePos.first.y);

	// ������ ����
	MathEngine::Vector2 destination = police->m_pathfind->m_findPotition->m_mapData[m_route[m_index]];
	MathEngine::Vector2 destinationCoo = m_route[m_index];
	police->m_pathfind->SetEndNode((int)destinationCoo.x, (int)destinationCoo.y);
	
	// A* ����
	police->m_pathfind->SolveAstar();

	// ������ �̵�
	MathEngine::Vector2 direction = (destination - location).Normalize();
	police->m_policeTrasnform->Translate(direction * (police->m_speed + 1.f) * deltaTime);

	// ���� ������ ����
	police->SetDirection(direction);
	
	// ��� Ȯ��
	if (policePos.first.x == destinationCoo.x && policePos.first.y == destinationCoo.y)
	{
		// ������ ���� (�ε���++)
		m_index++;
		m_index %= m_route.size();
	}
}

void PoliceIdleState::OnStateRender(DirectY* directY)
{

}

void PoliceIdleState::OnStateExit()
{
	
}
#pragma endregion IdleState

#pragma region ChasingState
void PoliceChasingState::OnStateEnter()
{

}

void PoliceChasingState::OnStateUpdate(float deltaTime)
{
	Police* police = (Police*)m_NPC;

	MathEngine::Vector2 m_policeLocation = police->m_policeTrasnform->GetLocalPosition() + MathEngine::Vector2(80.f, 90.f);
	MathEngine::Vector2 m_playerLocation = police->m_playerTransform->GetLocalPosition();

	// ���� ��ġ�� ��ã�� �˰��� ����Ѵ�
	police->m_pathfind->SetStartNode(m_policeLocation);

	// ������(�÷��̾��� ��ġ) ��ã�� �˰��� ����Ѵ�
	police->m_pathfind->SetEndNode(m_playerLocation);

	if (police->m_pathfind->onDestination())
	{
		MathEngine::Vector2 direction = (m_playerLocation - m_policeLocation).Normalize();
		police->m_policeTrasnform->Translate(direction * police->m_speed * deltaTime);
		return;
	}

	// A* ����
	police->m_pathfind->SolveAstar();

	if (police->m_pathfind->GetFinalPathNodeSize() < 2) return;

	// ���� �� �̵�
	m_objectLocation = police->m_pathfind->NearestLocation();
	MathEngine::Vector2 nextDirection = (m_objectLocation - m_policeLocation).Normalize();

	// ���� ������ ����
	police->SetDirection(nextDirection);

	police->m_policeTrasnform->Translate(nextDirection * police->m_speed * deltaTime);
}

void PoliceChasingState::OnStateRender(DirectY* directY)
{

}

void PoliceChasingState::OnStateExit()
{

}
#pragma endregion ChasingState

#pragma region CollisionState

PoliceCollisionState::PoliceCollisionState(NPC* npc)
	: BaseState(npc)
{
}

PoliceCollisionState::~PoliceCollisionState()
{
}

void PoliceCollisionState::OnStateEnter()
{
	Police* police = (Police*)m_NPC;
	Transform* policeTransform = (Transform*)(police->GetGameObject()->GetElement(ElementType::Transform));


	MathEngine::Vector2 location = policeTransform->GetLocalPosition();

	police->m_pathfind->SetStartNode(location);
	police->m_pathfind->SetEndNode(police->m_policeStation);
	police->m_pathfind->SolveAstar();


	int index = police->m_pathfind->GetFinalPathNodeSize();
	
	if (index < 4) return;

	police->m_policeTrasnform->SetLocalPosition(police->m_pathfind->GetLocation(index - 4));
	police->m_playerTransform->SetLocalPosition(police->m_pathfind->GetLocation(index - 1));

	Player* player = (Player*)(police->m_playerTransform->GetGameObject()->GetElement(ElementType::Script));
	player->BeCaught();
}

void PoliceCollisionState::OnStateUpdate(float deltaTime)
{
	Police* police = (Police*)m_NPC;
	MathEngine::Vector2 playerLocation = police->m_playerTransform->GetLocalPosition();

	// ���� ��ġ�� ��ã�� �˰��� ����Ѵ�
	police->m_pathfind->SetStartNode(playerLocation);

	// A* ����
	police->m_pathfind->SolveAstar();

	int index = police->m_pathfind->GetFinalPathNodeSize();

	/// ��� ��
	if (index < 4)
	{
		GameObject* playerObj = police->m_playerTransform->GetGameObject();
		playerObj->SetActive(false);
		police->SetIsInterrogated(true);

		// �ν� ������ ����
		police->m_recognizeRange = { 0.f, 0.f };

		// temp
		police->ChangeState(Police::State::Idle);
		return;
	}

	MathEngine::Vector2 policeObjectLocation = police->m_pathfind->GetLocation(index - 4) - MathEngine::Vector2(80.f, 90.f);
	MathEngine::Vector2 policeLocation = police->m_policeTrasnform->GetLocalPosition();
	MathEngine::Vector2 policeNextDirection = (policeObjectLocation - policeLocation).Normalize();;

	MathEngine::Vector2 PlayerObjectLocation = police->m_pathfind->GetLocation(index - 2);
	MathEngine::Vector2 objectNextDirection = (PlayerObjectLocation - playerLocation).Normalize();;

	police->m_policeTrasnform->Translate(policeNextDirection * (police->m_speed + 2.f) * deltaTime);
	police->m_playerTransform->Translate(objectNextDirection * (police->m_speed + 2.f) * deltaTime);

	// ���� ������ ����
	police->SetDirection(policeNextDirection);

	Vector2 cameraScale = CameraManager::GetInstance().GetCameraScale();

	/// �÷��̾� �� ī�޶�
	CameraManager::GetInstance().SetCameraPosition({ 
		-police->m_playerTransform->GetLocalPosition().x * cameraScale.x + 720,
		-police->m_playerTransform->GetLocalPosition().y * cameraScale.y + 540
		});
}

void PoliceCollisionState::OnStateRender(DirectY* directY)
{

}

void PoliceCollisionState::OnStateExit()
{
	Police* police = (Police*)m_NPC;
}
#pragma endregion CollisionState