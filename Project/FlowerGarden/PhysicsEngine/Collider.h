///
/// �浹ü �⺻ Ŭ���� �� �������̽��� 
/// 
/// �浹 �˰��� <- ���⼭ �̰� ���� �ִ°� �ſ� ���� �� ��
/// 

#pragma once

#include "CollisionPoints.h"

class DirectY;

namespace PhysicsEngine
{
	struct CircleCollider;
	struct RectangleCollider;
	struct IsometricCollider;
	struct VehicleCollider;

	struct Collider
	{
		MathEngine::Vector2 center;
		MathEngine::Vector2 initCenter;
		float m_degree = 0.f;

		virtual ~Collider() {};

		//  Collider �� ��ӹ޴� �ٸ� �浹ü����� �浹 �˻�
		virtual CollisionPoints TestCollision 
		(const Collider& collider) const = 0;

		// CircleCollider ���� �浹 �˻�
		virtual CollisionPoints TestCollision
		(const CircleCollider& circle) const = 0;

		// RectangleCollider ���� �浹 �˻�
		virtual CollisionPoints TestCollision
		(const RectangleCollider& rectangle) const = 0;

		// IsometricCollider ���� �浹 �˻�
		virtual CollisionPoints TestCollision
		(const IsometricCollider& isometric) const = 0;

		virtual void Update() = 0;

		virtual void DrawCollider(DirectY& draw) const = 0;

	protected:
		/// �� �� ��
		CollisionPoints CircleVsCircle
		(const CircleCollider& a, const CircleCollider& b) const;

		/// �� �� �׸�
		CollisionPoints CircleVsRectangle
		(const CircleCollider& a, const RectangleCollider& b) const;

		/// �׸� �� �׸�
		CollisionPoints RectangleVsRectangle
		(const RectangleCollider& a, const RectangleCollider& b) const;
		
		/// ������ �� ������ AABB
		CollisionPoints DiamondVsDiamond
		(const IsometricCollider& a, const IsometricCollider& b) const;

		/// �÷��̾� �� ������ Obb
		CollisionPoints VehicleVsDiamond (
			const VehicleCollider& v, const IsometricCollider& d) const;
	};
}