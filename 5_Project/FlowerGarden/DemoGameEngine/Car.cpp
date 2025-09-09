#include "Car.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"

Car::Car()
{

}

Car::~Car()
{

}

void Car::Init()
{

}

void Car::FixedUpdate()
{

}

void Car::Update(float deltaTime)
{

}

void Car::LateUpdate()
{

}

void Car::PreRender()
{

}

void Car::Render(DirectY* directY)
{

}

void Car::PostRender()
{

}

void Car::Release()
{

}

ElementType Car::GetElementType() const
{
	return ElementType::Script;
}

GameObject* Car::GetGameObject() const
{
	return m_gameObject;
}

void Car::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}
