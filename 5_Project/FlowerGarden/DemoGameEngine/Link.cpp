#include "Link.h"
#include "InputManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "../DirectY/Sprite.h"
#include "../DirectY/DirectY.h"

void Link::Init()
{

}

void Link::FixedUpdate()
{

}

void Link::Update(float deltaTime)
{
	//좌상단 이동
	if (InputManager::GetInstance().IsGetKeyDown(VK_LEFT))
	{
		//방향먼저 바꿔라
		//눌렀을때 애니메이션을 바꿔 줘야된다
		//애니메이션을 바꿔줄라면? 애니메이터를 만져야댐
		//링크 애니메이터를 알고있나? 혹은 링크 안에서 애니메이터에 접근가능한가
		

		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ -72 , -36 });		//0을 써야, Player와 함께 이동한다	
	}
	//우상단 이동
	if (InputManager::GetInstance().IsGetKeyDown(VK_UP))
	{
		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ 72 , -36 });
	}

	//좌하단 이동
	if (InputManager::GetInstance().IsGetKeyDown(VK_DOWN))
	{
		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ -72 , 36 });
	}
	//우하단 이동
	if (InputManager::GetInstance().IsGetKeyDown(VK_RIGHT))
	{
		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ 72 , 36 });
	}
}

void Link::LateUpdate()
{

}

void Link::PreRender()
{

}

void Link::Render(DirectY* directY)
{

}

void Link::PostRender()
{

}

void Link::Release()
{

}

ElementType Link::GetElementType() const
{
	return ElementType::Script;
}

GameObject* Link::GetGameObject() const
{
	return m_gameObject;
}

void Link::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}
