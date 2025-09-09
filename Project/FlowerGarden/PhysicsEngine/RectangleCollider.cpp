#include "RectangleCollider.h"

#include "CircleCollider.h"
#include "DirectY.h"

namespace PhysicsEngine
{

	RectangleCollider::RectangleCollider(
		float x, float y, float w, float h)
		: size(w, h)
	{
		this->center = MathEngine::Vector2(x, y);
	}

	RectangleCollider::RectangleCollider(
		MathEngine::Vector2 center, 
		MathEngine::Vector2 size)
		: size(size)
	{
		this->center = MathEngine::Vector2(center);
	}

	CollisionPoints RectangleCollider::TestCollision(const Collider& collider) const
	{
		return collider.TestCollision(*this);
	}

	CollisionPoints RectangleCollider::TestCollision(const CircleCollider& circle) const
	{
		return CircleVsRectangle(circle, *this);
	}

	CollisionPoints RectangleCollider::TestCollision(const RectangleCollider& rectangle) const
	{
		return RectangleVsRectangle(*this, rectangle);
	}

	CollisionPoints RectangleCollider::TestCollision(const IsometricCollider& isometric) const
	{
		return CollisionPoints();
	}

	void RectangleCollider::Update()
	{

	}

	void RectangleCollider::DrawCollider(DirectY& draw) const
	{

		Graphics::BaseFigure::Rectangle rectangle
		{
			center.x - size.x / 2.f, 
			center.y - size.y / 2.f, 
			center.x + size.x / 2.f,
			center.y + size.y / 2.f
		};

		Graphics::BaseFigure::Line slash
		{
			center.x - size.x / 2.f,
			center.y - size.y / 2.f,
			center.x,
			center.y
		};

		draw.DirectY::DrawLine(slash, 1.3f);
		draw.DirectY::DrawRectangle(rectangle, 1.8f);
	}
};