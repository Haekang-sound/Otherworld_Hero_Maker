#pragma once
#include "ElementBase.h"


class Hero : public ElementBase
{
public:
	Hero();
	~Hero();

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


private:
	//일반 시민과 크게 차이는 없다. 둘의 차이는 용사이냐 아니냐의 여부이므로
	bool isHero;	//이것이 true이면 Hero이다

	//플레이어와 충돌하면 사라진다
	bool isLiving;

	//충돌여부
	bool m_isCollided;
};

