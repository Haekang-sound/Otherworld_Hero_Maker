#pragma once

#include <vector>
#include <memory>

#include "Vector2.h"

class DirectY;

namespace PhysicsEngine
{
	struct Object;
	class Solver;
	struct Collision;
	struct CollisionPoints;

	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();

	public:
		// ������ü�� ������Ʈ�Ѵ�
		void Step(float dt);

		// �浹 �˻�
		void DetectCollisions(float dt);

		// ���� ó��
		void ResolveCollsion(
			std::vector<Collision>& collisions, 
			float dt);

		
		// ���� ��ü ������
		void Render(DirectY* draw);

		void AddObject(Object* object);
		void RemoveObject(Object* object);

		void AddSolver(Solver* solver);
		void RemoveSolver(Solver* solver);

		void SetScreenSize(float w, float h)
		{
			m_ScreenWidth = w;
			m_ScreenHeight = h;
		}

	private:
		std::vector<Object*> m_objects;
		std::vector<Solver*> m_solvers;

		// �߷� ���ӵ� 
		MathEngine::Vector2 m_gravity;

		// ȭ�� ũ��
		float m_ScreenWidth;
		float m_ScreenHeight;

		// ������ d2d ���� ��ü
		DirectY* m_draw;

		void TestResolve(
			Object& a, Object& b,
			const CollisionPoints& points);
	};
}