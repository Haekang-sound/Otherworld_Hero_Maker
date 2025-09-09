#pragma once

#include "ElementBase.h"

///오브젝트 생성시 기본사항: Element Base로부터 상속받아야 하고// Ctrl + H: abstrcat -> override 일괄변경 //   new로 생성하거나, 포인터로 생성한 것은 반드시 소멸자에서 제거해준다
class Player : public ElementBase
{
public:
	Player();
	~Player();

	//기본적으로 아래의 모든 함수는 모두 가져와서 쓴다
	virtual void Init() override;

	virtual void FixedUpdate() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;

	virtual void PreRender() override;
	virtual void Render(DirectY* directY) override;
	virtual void PostRender() override;

	virtual void Release() override;

	virtual ElementType GetElementType() const override;

	virtual GameObject* GetGameObject() const override;
	virtual void SetGameObject(GameObject* gameObject) override;
	//---------------------------------------------------------
private:
	//변수들
	//충돌여부
	bool m_isCollided;

	//앞뒤 방향지시등(좌,우) : 키를 입력받으면 on, off 할 것이며.. 가능하면.. 1번 입력하면 대기, 1번 더 입력하면 그 방향으로 이동한다고 하면 좋을 듯 
	bool m_leftLight;
	bool m_rightLight;

	//방향지시등 입력 횟수 //
	bool m_leftLightCount;	// 1은 지시등이 깜빡인다, 2되면 그 방향으로 이동하고, 이동이 끝난 후에는 다시 0으로 리셋된다
	bool m_rightLightCount;	//default는 우회전이므로 좌우 count를 따로 계산하는게 나을 듯
	///방향지시등 2번째 입력은 특정한 타일(좌우회전이 가능한 타일) 에서만 가능하다.
	///앞뒤 방향지시등은 함께 켜지고, 꺼진다

	//방향키 입력에 따른 정지, default는 전진, 우회전
	bool m_isGoing;	//기본은 전진상태

	//충돌위치에 따른 구분을 위해... 범퍼와 비 범퍼를 구분해야한다
	bool m_isBumper;		//그런데 이건 초기화하기가 힘든것이... 경찰차와 충돌하는부위에 따라 달라지는데?
	
};

