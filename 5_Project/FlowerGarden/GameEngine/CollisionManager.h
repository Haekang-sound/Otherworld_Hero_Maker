#pragma once

#include <map>
#include <memory>

#include "../MathEngine/Vector2.h"

// Component �̸��� Collider physicsEngine�� Collider�� ��ģ��.
// using namespace PhysicsEngine �� �ϸ� �ȵȴ�.
namespace PhysicsEngine
{
	struct Collider;
	struct CircleCollider;
	struct RectangleCollider;
	struct IsometricCollider;
	struct CollisionPoints;
}

class DirectY;
class GameObject;
class Collider;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Init();

	void Update(float deltaTime);

	// �Ƹ��� �׽�Ʈ�� ���� Render
	void Render(DirectY& directY);

	void Release();

	void AddCollider(GameObject* gameObject, Collider* collider);
	void DeleteCollider(GameObject* gameObject);

	// CollisionManager���� ���� Object �ʱ�ȭ�� �� Collider Element�� �߰�
	Collider* CreateCircleCollider(MathEngine::Vector2 center, float r);
	Collider* CreateRectangleCollider(float x, float y, float width, float height);
	Collider* CreateIsometricCollider(float x, float y, float height);
	Collider* CreateVehicleCollider(float x, float y, float height, float width);
	
	GameObject* GetPlayerObject() const { return m_playerObject; }
	void SetPlayerObject(GameObject* val) { m_playerObject = val; }

	Collider* GetPlayerCollider() const { return m_playerCollider; }
	void SetPlayerCollider(Collider* val) { m_playerCollider = val; }

private: 
	// Current Scene�� �����ϴ� ��� Collider�� �����ϱ� ���� ����
	// ������ GameObject���� �ϹǷ� delete �� �ص� ��
	// Collider�� Element�� Collider��
	std::multimap<GameObject*, Collider*> m_colliders;

	// �÷��̾��� ��ü�� �ݶ��̴� ����
	GameObject* m_playerObject;
	Collider* m_playerCollider;

	void ResolveCollsion( 
		GameObject* obj, 
		const PhysicsEngine::CollisionPoints& cp, 
		const float& dt, 
		bool& isTurnDirection);

	// ���� ���� �ݶ��̴��� ���ÿ� �浹���� �� ���� ��
	MathEngine::Vector2 m_playerNormal;
};