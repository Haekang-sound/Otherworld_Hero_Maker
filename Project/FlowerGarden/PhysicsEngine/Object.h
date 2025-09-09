///
/// �������� Ư���� ���� ����ü
///

#pragma once

#include "Vector2.h"
#include "Collider.h"

namespace PhysicsEngine
{
	struct Object
	{
		Object(
			MathEngine::Vector2 p,
			MathEngine::Vector2 v = MathEngine::Vector2(0.f, 0.f),
			MathEngine::Vector2 f = MathEngine::Vector2(0.f, 0.f),
			float m = 0.f);
		Object(MathEngine::Vector2 p, float m); 

		~Object();

		/// Rigidbody
		
		// ��ġ
		MathEngine::Vector2 position;
		// �ӵ�
		MathEngine::Vector2 velocity;
		// ��
		MathEngine::Vector2 force;
		// ����
		float mass;

		/// CollisionObject
		
		// �浹ü
		Collider* collider;
	};
}