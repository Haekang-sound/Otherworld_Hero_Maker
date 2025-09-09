#include "Police.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"

Police::Police()
{

}

Police::~Police()
{

}

void Police::Init()
{

}

void Police::FixedUpdate()
{

}

void Police::Update(float deltaTime)
{

}

void Police::LateUpdate()
{

}

void Police::PreRender()
{

}

void Police::Render(DirectY* directY)
{

}

void Police::PostRender()
{

}

void Police::Release()
{

}

ElementType Police::GetElementType() const
{
	return ElementType::Script;
}

GameObject* Police::GetGameObject() const
{
	return m_gameObject;
}

void Police::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}
