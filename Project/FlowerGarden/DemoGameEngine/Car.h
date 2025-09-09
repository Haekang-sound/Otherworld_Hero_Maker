#pragma once
#include "ElementBase.h"


class Car : public ElementBase
{
public:
	Car();
	~Car();

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


};

