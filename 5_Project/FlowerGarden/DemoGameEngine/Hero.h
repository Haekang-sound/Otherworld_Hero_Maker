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
	//�Ϲ� �ùΰ� ũ�� ���̴� ����. ���� ���̴� ����̳� �ƴϳ��� �����̹Ƿ�
	bool isHero;	//�̰��� true�̸� Hero�̴�

	//�÷��̾�� �浹�ϸ� �������
	bool isLiving;

	//�浹����
	bool m_isCollided;
};

