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
		// 물리객체를 업데이트한다
		void Step(float dt);

		// 충돌 검사
		void DetectCollisions(float dt);

		// 층돌 처리
		void ResolveCollsion(
			std::vector<Collision>& collisions, 
			float dt);

		
		// 물리 객체 랜더링
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

		// 중력 가속도 
		MathEngine::Vector2 m_gravity;

		// 화면 크기
		float m_ScreenWidth;
		float m_ScreenHeight;

		// 디버깅용 d2d 앤진 객체
		DirectY* m_draw;

		void TestResolve(
			Object& a, Object& b,
			const CollisionPoints& points);
	};
}