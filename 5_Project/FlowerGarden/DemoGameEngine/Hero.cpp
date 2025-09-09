#include "Hero.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"

Hero::Hero()
{

}

Hero::~Hero()
{

}

void Hero::Init()
{

}

void Hero::FixedUpdate()
{

}

void Hero::Update(float deltaTime)
{

}

void Hero::LateUpdate()
{

}

void Hero::PreRender()
{

}

void Hero::Render(DirectY* directY)
{

}

void Hero::PostRender()
{

}

void Hero::Release()
{

}

ElementType Hero::GetElementType() const
{
	return ElementType::Script;
}

GameObject* Hero::GetGameObject() const
{
	return m_gameObject;
}

void Hero::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}
