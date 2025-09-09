#pragma once

#include <memory>

#include "ElementBase.h"
#include "../PhysicsEngine/Collider.h"

#include <d2d1.h>

// Component �̸��� Collider physicsEngine�� Collider�� ��ģ��.
// using namespace PhysicsEngine �� �ϸ� �ȵȴ�.
namespace PhysicsEngine { struct Collider; }

class Collider : public ElementBase
{
public:
	Collider();
	~Collider();

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


	/// ������ & ������
	PhysicsEngine::Collider* GetCollider() { return m_collider.get(); }
	void SetCollider(std::unique_ptr<PhysicsEngine::Collider> collider) { m_collider = std::move(collider); }

	bool GetIsCollision() const { return m_isCollision; }
	void SetIsCollision(bool isCollision) { m_isCollision = isCollision; }
private:
	// �ö��̴��� �浹 ����
	bool m_isCollision;
	// ���� ������ �ö��̴�
	std::unique_ptr<PhysicsEngine::Collider> m_collider;
};