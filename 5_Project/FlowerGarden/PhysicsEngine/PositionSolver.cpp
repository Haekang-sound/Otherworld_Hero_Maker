#include "PositionSolver.h"

#include "Vector2.h"
#include "Object.h"
#include "Collision.h"

namespace PhysicsEngine
{
	void PositionSolver::Solve(
		std::vector<Collision>& collisions, float dt)
	{
		/*
		for (Collision& collsion : collisions)
		{
			Object* aBody = collsion.objA;
			Object* bBody = collsion.objB;

			MathEngine::Vector2 resolution =
				collsion.points.normal *
				collsion.points.depth;

			// �̷��ٰ� �ݿ����� �ʴ´�.
			aBody->transform->position -= resolution;
			bBody->transform->position += resolution;
		}
		
		collisions.clear();
		*/
	}
}
