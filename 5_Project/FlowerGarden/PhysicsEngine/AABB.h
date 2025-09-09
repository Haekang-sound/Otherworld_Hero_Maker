///
/// AABB �浹 ó�� �˰���
/// ��ü���� �ּ�, �ִ� x, y ��ǥ�� �̿��Ͽ� �浹 ���θ� �Ǵ�
/// 

#pragma once

#include "ICollisionDetection.h"
#include "Vector2.h"

class AABB
	: public ICollisionDetection
{
public:
	AABB();
	~AABB();

	virtual void CheckCollision() override;
	virtual void Render(DirectY& directY) const override;


	void SetAabbTarget(AABB* val) { m_aabbTarget = val; }

	bool GetCollide() const { return m_isCollide; }
	void SetCollide(bool val) { m_isCollide = val; }


	Vector2 GetLeftTop() const { return m_leftTop; }
	void SetLeftTop(Vector2 val) { m_leftTop = val; }

	Vector2 GetRightBottom() const { return m_rightBottom; }
	void SetRightBottom(Vector2 val) { m_rightBottom = val; }

private:
	AABB* m_aabbTarget;
	bool m_isCollide;

	Vector2 m_leftTop;
	Vector2 m_rightBottom;

	bool CalculateCollision(const AABB& other) const;
};

