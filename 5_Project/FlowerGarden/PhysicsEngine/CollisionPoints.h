///
/// �� ���� ��ü�� �浹�� ������ 
/// �浹 ���� ������ ���� ����ü
/// 

#pragma once

#include "Vector2.h"

namespace PhysicsEngine
{
	struct CollisionPoints
	{
		// ��ü A �� �浹 ��ġ ����
		MathEngine::Vector2 a = (0.f, 0.f);
		// ��ü B �� �浹 ��ġ ����
		MathEngine::Vector2 b = (0.f, 0.f);
		// �� ��ü ������ �浹 ���� ����
		MathEngine::Vector2 normal = (0.f, 0.f);
		// �� ��ü�� �浹 ����
		float depth = 0.0f;
		// �浹 �߻� ����
		bool hasCollision = false;

	public:
		// �浹���� ���� ���·� �ʱ�ȭ
		void Reset();
	};
}