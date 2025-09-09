#include "Player.h"
#include "InputManager.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"		//

// temp TEst
#include "../DirectY/DirectY.h"

///�÷��̾� Ŭ���� ����
Player::Player()
	:m_isCollided(false),
	m_leftLight(false), m_leftLightCount(false),
	m_rightLight(true), m_rightLightCount(true),
	m_isGoing(true)
{

}

Player::~Player()
{

}

void Player::Init()
{
	//�÷��̾� �ʱ�ȭ
	//�����ڿ��� �ʱ�ȭ�ߴµ�, Init������ ����� �ʱ�ȭ�ؾ��ұ�?
}

//���� ������Ʈ ����: �浹(���, �Ϲݽù�, ����) or �ٸ��� ������ �߰�
void Player::FixedUpdate()
{
// 	if (m_isCollided == true)	//�浹
// 	{
// 		//1. ���� �浹 : ���� �������, �̰� ������� ǥ���ϸ� �ɰŰ��� 
// 		if ()	//������.. �浹�Լ��� ���� ������ ������ �� ����
// 		{
// 		}
// 
// 		//2. �ùΰ� �浹 :  ���������ֱ�+ 1 �ö󰣴�(���������� �����ϸ� ������?), �ù��� �������, 
// 		else if ()
// 		{
// 		}
// 
// 		//3. �ٸ� ������ �浹 : ���������ֱ� +1
// 		else if ()
// 		{
// 		}
// 
// 
// 		//4. ������ �浹 : ���� ���� ? �ö󰣴� ... ���� ���θ� �����°� ���� ��ƴ�. Ʈ���� �κ����� ������ �ҰŰ�����...?
// 		if ()	//���ۿ� : ��縦 �̼��� ��������
// 		{
// 
// 		}
// 		else    //���� �̿ܿ� : ü��
// 		{
// 			//���� �ð� �Ŀ� ���� �������Ѵ�
// 		}
// 
// 	}
}


void Player::Update(float deltaTime)
{
	///Ű �Է¿� ���� �̵�, ����: Ʈ���� ������ ����, �̵��� �� ������ �ٲ���Ѵ�
	///Ʈ���� ��(�»��, ����)���� �̵��ϰ� ���� ���� �Ʒ� �� Ű �Է��� ���ƾ� �ҵ�... �ƴѰ�? 
	//�»�� �̵�
	if (InputManager::GetInstance().IsGetKeyDown(VK_LEFT))	//InputManager::GetInstance()�� className&���� ��ü�� ��ȯ�ϱ� ������ . ���� ����Լ� ���ٰ���
	{
		//������� �ٲ��

		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ -144 , -72 });	//2:1�� �����ε�. 144, 72�� �������� ��ȣ�� �ٲ� �����̴�
	}
	//���� �̵�
	if (InputManager::GetInstance().IsGetKeyDown(VK_UP))
	{

		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ 144 , -72 });
	}

	///Ʈ���� �Ʒ��� �̵��ϰ� �������� ���� �� Ű �Է��� ���ƾ��ҵ�
	//���ϴ� �̵�
	if (InputManager::GetInstance().IsGetKeyDown(VK_DOWN))
	{

		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ -144 , 72 });
	}
	//���ϴ� �̵�
	if (InputManager::GetInstance().IsGetKeyDown(VK_RIGHT))
	{

		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ 144 , 72 });
	}


	//�Է��� ���ٸ�, �ٶ󺸴� �������� 0.5�ʿ� 1ĭ�� �̵��Ѵ�
	//if ()
	//{
	//	//
	//}
}

void Player::LateUpdate()
{

}

void Player::PreRender()
{

}

void Player::Render(DirectY* directY)
{
	directY->SetBrushColor(0, 1, 0, 1);
	directY->DrawRectangle({	//����: �簢���� �»��, ���ϴ� ������
		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->GetLocalPosition().x - 10,	 
		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->GetLocalPosition().y - 20, 
		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->GetLocalPosition().x + 10,
		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->GetLocalPosition().y + 20 
		});
}

void Player::PostRender()
{

}

void Player::Release()
{
	//�Ҹ��ڿ��� �����ϴ°Ŷ� �򰥸��µ� ���� �� ������ ������
}

ElementType Player::GetElementType() const
{
	return ElementType::Script;
}

GameObject* Player::GetGameObject() const
{
	return m_gameObject;
}

void Player::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}
