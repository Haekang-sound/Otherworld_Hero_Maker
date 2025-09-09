#include "Player.h"
#include "InputManager.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"		//

// temp TEst
#include "../DirectY/DirectY.h"

///플레이어 클래스 생성
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
	//플레이어 초기화
	//생성자에서 초기화했는데, Init에서는 어떤것을 초기화해야할까?
}

//물리 업데이트 관련: 충돌(용사, 일반시민, 경찰) or 다른거 있으면 추가
void Player::FixedUpdate()
{
// 	if (m_isCollided == true)	//충돌
// 	{
// 		//1. 용사와 충돌 : 용사는 사라진다, 이건 용사한테 표시하면 될거같다 
// 		if ()	//조건은.. 충돌함수를 만든 다음에 가능할 것 같다
// 		{
// 		}
// 
// 		//2. 시민과 충돌 :  경찰생성주기+ 1 올라간다(전역변수로 선언하면 좋을듯?), 시민은 사라진다, 
// 		else if ()
// 		{
// 		}
// 
// 		//3. 다른 차량과 충돌 : 경찰생성주기 +1
// 		else if ()
// 		{
// 		}
// 
// 
// 		//4. 경찰과 충돌 : 유죄 경고등 ? 올라간다 ... 범퍼 여부를 나누는게 조금 어렵다. 트럭을 부분으로 나눠서 할거같은데...?
// 		if ()	//범퍼에 : 용사를 이세계 면접으로
// 		{
// 
// 		}
// 		else    //범퍼 이외에 : 체포
// 		{
// 			//일정 시간 후에 새로 리스폰한다
// 		}
// 
// 	}
}


void Player::Update(float deltaTime)
{
	///키 입력에 따른 이동, 기준: 트럭의 운전자 시점, 이동할 때 방향을 바꿔야한다
	///트럭이 위(좌상단, 우상단)으로 이동하고 있을 때는 아래 두 키 입력을 막아야 할듯... 아닌가? 
	//좌상단 이동
	if (InputManager::GetInstance().IsGetKeyDown(VK_LEFT))	//InputManager::GetInstance()는 className&형의 객체를 반환하기 때문에 . 으로 멤버함수 접근가능
	{
		//방향먼저 바꿔라

		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ -144 , -72 });	//2:1의 비율인데. 144, 72의 조합으로 부호를 바꿀 예정이다
	}
	//우상단 이동
	if (InputManager::GetInstance().IsGetKeyDown(VK_UP))
	{

		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ 144 , -72 });
	}

	///트럭이 아래로 이동하고 있을때는 위의 두 키 입력을 막아야할듯
	//좌하단 이동
	if (InputManager::GetInstance().IsGetKeyDown(VK_DOWN))
	{

		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ -144 , 72 });
	}
	//우하단 이동
	if (InputManager::GetInstance().IsGetKeyDown(VK_RIGHT))
	{

		((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->Translate({ 144 , 72 });
	}


	//입력이 없다면, 바라보는 방향으로 0.5초에 1칸씩 이동한다
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
	directY->DrawRectangle({	//변수: 사각형의 좌상단, 우하단 꼭지점
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
	//소멸자에서 해제하는거랑 헷갈리는데 조금 더 설명을 들어야함
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
