#include "CircleCollider.h"

#include "RectangleCollider.h"
#include "DirectY.h"
#include "Constants.h"

namespace PhysicsEngine
{

	CircleCollider::CircleCollider(float x, float y, float r)
		: radius(r)
	{
		this->center = MathEngine::Vector2(x, y);
	}

	CircleCollider::CircleCollider(MathEngine::Vector2 center, float r)
		: radius(r)
	{
		this->center = center;
	}

	CollisionPoints CircleCollider::TestCollision(const Collider& collider) const
	{
		return collider.TestCollision(*this);
	}

	CollisionPoints CircleCollider::TestCollision(const CircleCollider& circle) const
	{
		return CircleVsCircle(*this, circle);
	}

	CollisionPoints CircleCollider::TestCollision(const RectangleCollider& rectangle) const
	{
		return CircleVsRectangle(*this, rectangle);
	}

	CollisionPoints CircleCollider::TestCollision(const IsometricCollider& isometric) const
	{
		return CollisionPoints();
	}

	void CircleCollider::Update()
	{

	}

	void CircleCollider::DrawCollider(DirectY& draw) const
	{
		Graphics::BaseFigure::Circle circle
		{
			center.x, center.y, radius
		};

		Graphics::BaseFigure::Line slash
		{
			center.x,
			center.y,
			center.x - radius * MathEngine::Constant::SQRT2_OVER_2,
			center.y - radius * MathEngine::Constant::SQRT2_OVER_2
		};

		draw.DirectY::DrawLine(slash, 1.3f);
		draw.DirectY::DrawCircle(circle, 1.8f);
	}
}