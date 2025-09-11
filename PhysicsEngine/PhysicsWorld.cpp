#include "PhysicsWorld.h"

#include "Object.h"
#include "Solver.h"
#include "Collision.h"
#include "DirectY.h"

#include <windowsx.h>

namespace PhysicsEngine
{
	PhysicsWorld::PhysicsWorld()
		: m_objects{}
		, m_solvers{}
		, m_gravity(0.f, 9.81f)
		, m_ScreenWidth(1920.f)
		, m_ScreenHeight(1080.f)
		, m_draw(nullptr)
	{

	}

	PhysicsWorld::~PhysicsWorld()
	{
		for (Object* obj : m_objects)
		{
			delete obj;
		}
		m_objects.clear();

		for (Solver* solver : m_solvers)
		{
			delete solver;
		}
		m_solvers.clear();
	}

	void PhysicsWorld::Step(float dt)
	{
		for (Object* obj : m_objects)
		{
			// 오브젝트 위치 업뎃
			obj->force += m_gravity * obj->mass;
			obj->velocity += obj->force / obj->mass * dt;
			obj->position += obj->velocity * dt;

			// 충돌체 위치 업뎃
			obj->collider->center = obj->position;

			// 화면 밖으로 나간다면
			if (obj->position.x >= m_ScreenWidth) obj->position.x -= m_ScreenWidth;
			if (obj->position.y >= m_ScreenHeight) obj->position.y -= m_ScreenHeight;
			if (obj->position.x < 0) obj->position.x += m_ScreenWidth;
			if (obj->position.y < 0) obj->position.y += m_ScreenHeight;

			if (obj->velocity.Magnitude() < 0.001f)
			{
				//obj->force = MathEngine::Vector2(0, 0);
				obj->velocity = MathEngine::Vector2(0, 0);
			}
		}
	}

	void PhysicsWorld::DetectCollisions(float dt)
	{
		std::vector<Collision> collisions;

		for (Object* a : m_objects)
		{
			if (!a->collider) break;

			for (Object* b : m_objects)
			{
				if (a == b) break;

				if (!a->collider || !b->collider) continue;

				CollisionPoints points =
 					a->collider->TestCollision(*b->collider);

				/// 충돌 감지
				if (points.hasCollision)
				{
					if (m_draw)
					{
						m_draw->SetBrushColor(D2D1::ColorF::Red);
						
						Graphics::BaseFigure::Line slash1
						{
							a->position.x,
							a->position.y,
							points.a.x,
							points.a.y
						};

						m_draw->DirectY::DrawLine(slash1, 1.8f);
					
						Graphics::BaseFigure::Line slash2
						{
							b->position.x,
							b->position.y,
							points.b.x,
							points.b.y
						};
						
						m_draw->DirectY::DrawLine(slash2, 1.8f);
					}

					/// 충돌 해결 - 아직 하는 일 없음
					collisions.emplace_back(a, b, points);
					ResolveCollsion(collisions, dt);

					TestResolve(*a, *b, points);

					// a->collider->OnCollisionEnter()
					// a->collider->OnCollisionStay()
					// a->collider->OnCollisionExit()

					// b->collider->OnCollisionEnter()
					// b->collider->OnCollisionStay()
					// b->collider->OnCollisionExit()
				}
			}
		}
	}

	// 충돌 해결 하는 일 없음
	void PhysicsWorld::ResolveCollsion(
		std::vector<Collision>& collisions, float dt)
	{
		for (Solver* solver : m_solvers)
		{
			solver->Solve(collisions, dt);
		}
	}

	void PhysicsWorld::Render(DirectY* draw)
	{
		// 이러면 분기가 생기는 거라
		// 매우 불편한 마음이 듦
		if (!m_draw) m_draw = draw;

		for (Object* obj : m_objects)
		{
			//obj->collider->DrawCollider(*m_draw, TODO);
		}

		for (Solver* solver : m_solvers)
		{
		}
	}

	void PhysicsWorld::AddObject(Object* object)
	{
		m_objects.push_back(object);
	}

	void PhysicsWorld::RemoveObject(Object* object)
	{
		if (!object)
		{
			return;
		}

		auto itr = std::find
		(
			m_objects.begin(), m_objects.end(), object
		);

		if (itr == m_objects.end())
		{
			return;
		}

		delete* itr;

		m_objects.erase(itr);
	}

	void PhysicsWorld::AddSolver(Solver* solver)
	{
		m_solvers.push_back(solver);
	}

	void PhysicsWorld::RemoveSolver(Solver* solver)
	{
		if (!solver)
		{
			return;
		}

		auto itr = std::find
		(
			m_solvers.begin(), m_solvers.end(), solver
		);

		if (itr == m_solvers.end())
		{
			return;
		}
		
		delete *itr;

		m_solvers.erase(itr);
	}

	void PhysicsWorld::TestResolve(
		Object& a, Object& b, const CollisionPoints& points)
	{
		float dis = a.position.Distance(b.position);
		a.position +=
			points.normal * points.depth / dis;
		b.position -=
			points.normal * points.depth / dis;
	}

}