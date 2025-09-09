#pragma once
#include "ElementBase.h"


class Police : public ElementBase
{
public:
	Police();
	~Police();

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
	//충돌여부
	bool m_isCollided;

	//경찰생성주기? (주기가 길어지면 안좋은건데...)
	int m_policeCount;	//이렇게 해도 괜찮은가? 아무리봐도 전역변수가 나은거같은데?
};

