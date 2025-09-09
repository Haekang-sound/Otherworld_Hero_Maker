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
	//�»�� �̵�
	if (InputManager::GetInstance().IsGetKeyDown(VK_LEFT))
	{
		//������� �ٲ��
		//�������� �ִϸ��̼��� �ٲ� ��ߵȴ�
		//�ִϸ��̼��� �ٲ��ٶ��? �ִϸ����͸� �����ߴ�
		//��ũ �ִϸ����͸� �˰��ֳ�? Ȥ�� ��ũ �ȿ��� �ִϸ����Ϳ� ���ٰ����Ѱ�
		

		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ -72 , -36 });		//0�� ���, Player�� �Բ� �̵��Ѵ�	
	}
	//���� �̵�
	if (InputManager::GetInstance().IsGetKeyDown(VK_UP))
	{
		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ 72 , -36 });
	}

	//���ϴ� �̵�
	if (InputManager::GetInstance().IsGetKeyDown(VK_DOWN))
	{
		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ -72 , 36 });
	}
	//���ϴ� �̵�
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
