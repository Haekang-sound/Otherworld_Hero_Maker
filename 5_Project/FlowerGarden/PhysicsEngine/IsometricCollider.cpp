#include "IsometricCollider.h"

#include "DirectY.h"
#include "Constants.h"

namespace PhysicsEngine 
{
	IsometricCollider::IsometricCollider(
		float x, float y)
		: width(144.f)
		, height(72.f)
	{
		this->center = MathEngine::Vector2(x, y);
		this->initCenter = MathEngine::Vector2(x, y);
	}

	IsometricCollider::IsometricCollider(
		float x, float y, float h = 72.f)
		: width(h * 2.f)
		, height(h)
	{
		this->center = MathEngine::Vector2(x, y);
		this->initCenter = MathEngine::Vector2(x, y);
	}

	IsometricCollider::IsometricCollider(
		MathEngine::Vector2 center, float h = 72.f)
		: width(h * 2.f)
		, height(h)
	{
		this->center = center;
		this->initCenter = center;
	}

	CollisionPoints IsometricCollider::TestCollision(const Collider& collider) const
	{
		return collider.TestCollision(*this);
	}

	CollisionPoints IsometricCollider::TestCollision(const CircleCollider& circle) const
	{
		return CollisionPoints();
	}

	CollisionPoints IsometricCollider::TestCollision(const RectangleCollider& rectangle) const
	{
		return CollisionPoints();
	}


	CollisionPoints IsometricCollider::TestCollision(const IsometricCollider& isometric) const
	{
		return DiamondVsDiamond(*this, isometric);
	}

	void IsometricCollider::Update()
	{

	}

	void IsometricCollider::DrawCollider(DirectY& draw) const
	{
		draw.DrawIsometric(Graphics::BaseFigure::IsomatricTile
		{Graphics::BaseFigure::Point {initCenter.x, initCenter.y}, height / 2.f, width / 2.f}, 2.18f);
	}
}

