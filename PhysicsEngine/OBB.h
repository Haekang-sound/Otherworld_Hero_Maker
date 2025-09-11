///
/// OBB �浹 ó�� �˰���
/// ��ü���� �߽���, ũ��, ȸ�� ���� ���� �̿��Ͽ� �浹 ���θ� �Ǵ�
/// 

#pragma once

#include "ICollisionDetection.h"
#include "Vector2.h"
#include "Constants.h"

class OBB
	: public ICollisionDetection
{
public:
	OBB();
	~OBB();

	virtual void CheckCollision() override;
	virtual void Render(DirectY& directY) const override;


	OBB* GetObbTarget() const { return m_obbTarget; }
	void SetObbTarget(OBB* val) { m_obbTarget = val; }

	bool GetCollide() const { return m_isCollide; }
	void SetCollide(bool val) { m_isCollide = val; }

	Vector2 GetCenterPos() const { return m_centerPos; }
	void SetCenterPos(Vector2 val) { m_centerPos = val; }

	Vector2 GetSize() const { return m_size; }
	void SetSize(Vector2 val) { m_size = val; }

	float GetRotation() const { return m_rotation; }
	void SetRotation(float val) { m_rotation = val; }

private:
	OBB* m_obbTarget;
	bool m_isCollide;

	Vector2 m_centerPos;
	Vector2 m_size;
	float m_rotation;

	bool CalculateCollision(const OBB& other) const;
};

