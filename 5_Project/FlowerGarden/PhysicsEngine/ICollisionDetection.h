///
/// �浹 ���� Ŭ������ �������̽��� ���� �߻� Ŭ����
/// 

#pragma once

class DirectY;

class ICollisionDetection
{
public:
	virtual ~ICollisionDetection() {}

	virtual void CheckCollision() abstract;

	// ������� ���� �浹���� �׸���
	virtual void Render(DirectY& directY) const abstract;
};