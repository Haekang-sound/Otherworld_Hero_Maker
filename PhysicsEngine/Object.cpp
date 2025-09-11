#include "Object.h"

namespace PhysicsEngine
{
	Object::Object
	(
		MathEngine::Vector2 p,
		MathEngine::Vector2 v,
		MathEngine::Vector2 f,
		float m
	)
		: position(p)
		, velocity(v)
		, force(f)
		, mass(m)
		, collider(nullptr)
	{

	}

	Object::Object(MathEngine::Vector2 p, float m)
		: position(p)
		, velocity{ 0.f, }
		, force{ 0.f, }
		, mass(m)
		, collider(nullptr)
	{

	}

	Object::~Object()
	{
		if (collider) delete collider;
	}

}