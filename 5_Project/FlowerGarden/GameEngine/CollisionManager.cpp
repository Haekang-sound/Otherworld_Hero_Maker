#include <algorithm>

#include "CollisionManager.h"

#include "GameObject.h"
#include "Collider.h"
#include "Transform.h"
#include "../GameProcess/Player.h"

#include "../DirectY/DirectY.h"

#include "../PhysicsEngine/CircleCollider.h"
#include "../PhysicsEngine/RectangleCollider.h"
#include "../PhysicsEngine/IsometricCollider.h"
#include "../PhysicsEngine/VehicleCollider.h"
#include "../PhysicsEngine/CollisionPoints.h"

#include "../MathEngine/MathUtils.h"

#include "CameraManager.h"
#include "../GameProcess/DebugManager.h"
#include "../GameProcess/Police.h"

//#include <string>
CollisionManager::CollisionManager()
	: m_playerObject(nullptr)
	, m_playerCollider(nullptr)
	, m_playerNormal({})
{

}

CollisionManager::~CollisionManager()
{
	for (auto& collision : m_colliders)
	{
		// �ǹ��� �浹ü�� ���� �����ش�.
		if (collision.first->GetName() == "TileManager")
		{
			delete collision.second;
		}
	}
}

void CollisionManager::Init()
{
	for (auto& collision : m_colliders)
	{
		// �ǹ��� �浹ü�� ���� �����ش�.
		if (collision.first->GetName() == "TileManager")
		{
			delete collision.second;
		}
	}
	m_colliders.clear();
}

void CollisionManager::Update(float deltaTime)
{
	/// ���� ó��
	if (m_colliders.empty()) return;
	
	float val = ((Player*)(m_playerObject->GetElement(ElementType::Script)))->GetSpeed();
	//if (/*MathEngine::isEqual(val, 0.f) &&*/ m_playerCollider->GetIsCollision() == false) return;

	bool isReversed = false;

	int collisionCount = 0;
	m_playerNormal = {};

	/// �÷��̾� vs �ٸ� ���� ������Ʈ
	for (const auto& collider : m_colliders)
	{
		const PhysicsEngine::Collider& testCollider =
			*collider.second->GetCollider();

		PhysicsEngine::CollisionPoints point = 
			m_playerCollider->GetCollider()->TestCollision(testCollider);

		// �浹�� ���
		if (point.hasCollision)
		{
			// �ٸ� ���� ������Ʈ�� �浹�� ��
			collider.second->SetIsCollision(true);
			ResolveCollsion(collider.first, point, deltaTime, isReversed);
			if (collider.first->GetName() == "TileManager")
			{
				collisionCount++;
			}
			if (collider.first->GetName().find("Car_") != std::string::npos)
			{
				collisionCount++;
			}
		}
		else
		{
			collider.second->SetIsCollision(false);
		}
	}

	Player* player = ((Player*)(m_playerObject->GetElement(ElementType::Script)));
	if (collisionCount > 0)
	{
		player->SetMoveVector(m_playerNormal.Normalize());
		player->SetStun(true);
	}

	isReversed = false;

	// �÷��̾��� �浹���� �˻�
	for (const auto& collider : m_colliders)
	{
		if (collider.second->GetIsCollision())
		{
			m_playerCollider->SetIsCollision(true);
			return;
		}

		m_playerCollider->SetIsCollision(false);
	}
}

void CollisionManager::ResolveCollsion(
	GameObject* obj,
	const PhysicsEngine::CollisionPoints& cp,
	const float& dt,
	bool& isTurnDirection)
{
	if (obj->GetName() == "TileManager")
	{
		m_playerNormal += cp.normal;
	}

	if (obj->GetName() == "Police")
	{
		//Police* police = (Police*)(obj->GetElement(ElementType::Script));
		//police->ChangeState(Police::State::Collision);
	}

	if (obj->GetName() == "�ù�")
	{
		/* ����: �ù��� ������ �����Ѵ�...*/

		//delete otherObject;
	}

	if (obj->GetName().find("Car_") != std::string::npos)
	{
		m_playerNormal += cp.normal;
	}

}

void CollisionManager::Render(DirectY& directY)
{
	if (DebugManager::GetInstance().GetIsDebuging())
	{
		directY.SetTransform(CameraManager::GetInstance().GetCameraMatrix());
		for (auto& collider : m_colliders)
		{
			if (collider.first->GetName() == "TileManager")
				collider.second->Render(&directY);
		}
	}
}

void CollisionManager::Release()
{

}

void CollisionManager::AddCollider(
	GameObject* gameObject, Collider* collider)
{
	m_colliders.insert({ gameObject, collider });
}

void CollisionManager::DeleteCollider(GameObject* gameObject)
{
	m_colliders.erase(gameObject);
}

Collider* CollisionManager::CreateCircleCollider(
	MathEngine::Vector2 center, float r)
{
	// ��ȯ�� ���� ������ �浹ü
	std::unique_ptr<Collider> tempCollider =
		std::make_unique<Collider>();

	// ���� ������ �浹ü
	std::unique_ptr<PhysicsEngine::Collider> engineCollider =
		std::make_unique<PhysicsEngine::CircleCollider>(center, r);
	tempCollider->SetCollider(std::move(engineCollider));

	// �Ҵ� ���� �� ������ ����
	return tempCollider.release();
}

Collider* CollisionManager::CreateRectangleCollider(
	float x, float y, float width, float height)
{
	// ��ȯ�� ���� ������ �浹ü
	std::unique_ptr<Collider> tempCollider =
		std::make_unique<Collider>();

	// ���� ������ �浹ü
	std::unique_ptr<PhysicsEngine::Collider> engineCollider =
		std::make_unique<PhysicsEngine::RectangleCollider>(
			x, y, width, height);
	tempCollider->SetCollider(std::move(engineCollider));

	// �Ҵ� ���� �� ������ ����
	return tempCollider.release();
}

Collider* CollisionManager::CreateIsometricCollider(
	float x, float y, float height)
{
	// ��ȯ�� ���� ������ �浹ü
	std::unique_ptr<Collider> tempCollider = 
		std::make_unique<Collider>();

	// ���� ������ �浹ü
	std::unique_ptr<PhysicsEngine::Collider> engineCollider =
		std::make_unique<PhysicsEngine::IsometricCollider>
		(x, y, height);
	tempCollider->SetCollider(std::move(engineCollider));

	// �Ҵ� ���� �� ������ ����
	return tempCollider.release();
}

Collider* CollisionManager::CreateVehicleCollider(
	float x, float y, float height, float width)
{
	// ��ȯ�� ���� ������ �浹ü
	std::unique_ptr<Collider> tempCollider = 
		std::make_unique<Collider>();

	// ���� ������ �浹ü
	std::unique_ptr<PhysicsEngine::Collider> engineCollider =
		std::make_unique<PhysicsEngine::VehicleCollider>
		(x, y, height, width);
	tempCollider->SetCollider(std::move(engineCollider));

	// �Ҵ� ���� �� ������ ����
	return tempCollider.release();
}