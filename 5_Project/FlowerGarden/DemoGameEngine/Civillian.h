#pragma once
#include "ElementBase.h"


class Civillian : public ElementBase
{
public:
	Civillian();
	~Civillian();

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
	//������
	//�Ϲ� �ùΰ� ũ�� ���̴� ����. ���� ���̴� ����̳� �ƴϳ��� �����̹Ƿ�
	bool isHero;	//�̰��� false�̸� Civillian�̴�

	//�÷��̾�� �浹�ϸ� �������
	bool isLiving;	//false�� �Ǹ� �̼��� ������������

	//�浹����
	bool m_isCollided;

};

