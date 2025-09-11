#include "Civillian.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"

Civillian::Civillian()
{

}

Civillian::~Civillian()
{

}

void Civillian::Init()
{

}

void Civillian::FixedUpdate()
{

}

void Civillian::Update(float deltaTime)
{

}

void Civillian::LateUpdate()
{

}

void Civillian::PreRender()
{

}

void Civillian::Render(DirectY* directY)
{

}

void Civillian::PostRender()
{

}

void Civillian::Release()
{

}

ElementType Civillian::GetElementType() const
{
	return ElementType::Script;
}

GameObject* Civillian::GetGameObject() const
{
	return m_gameObject;
}

void Civillian::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}
