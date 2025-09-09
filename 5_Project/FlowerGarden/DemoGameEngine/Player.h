#pragma once

#include "ElementBase.h"

///������Ʈ ������ �⺻����: Element Base�κ��� ��ӹ޾ƾ� �ϰ�// Ctrl + H: abstrcat -> override �ϰ����� //   new�� �����ϰų�, �����ͷ� ������ ���� �ݵ�� �Ҹ��ڿ��� �������ش�
class Player : public ElementBase
{
public:
	Player();
	~Player();

	//�⺻������ �Ʒ��� ��� �Լ��� ��� �����ͼ� ����
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
	//������
	//�浹����
	bool m_isCollided;

	//�յ� �������õ�(��,��) : Ű�� �Է¹����� on, off �� ���̸�.. �����ϸ�.. 1�� �Է��ϸ� ���, 1�� �� �Է��ϸ� �� �������� �̵��Ѵٰ� �ϸ� ���� �� 
	bool m_leftLight;
	bool m_rightLight;

	//�������õ� �Է� Ƚ�� //
	bool m_leftLightCount;	// 1�� ���õ��� �����δ�, 2�Ǹ� �� �������� �̵��ϰ�, �̵��� ���� �Ŀ��� �ٽ� 0���� ���µȴ�
	bool m_rightLightCount;	//default�� ��ȸ���̹Ƿ� �¿� count�� ���� ����ϴ°� ���� ��
	///�������õ� 2��° �Է��� Ư���� Ÿ��(�¿�ȸ���� ������ Ÿ��) ������ �����ϴ�.
	///�յ� �������õ��� �Բ� ������, ������

	//����Ű �Է¿� ���� ����, default�� ����, ��ȸ��
	bool m_isGoing;	//�⺻�� ��������

	//�浹��ġ�� ���� ������ ����... ���ۿ� �� ���۸� �����ؾ��Ѵ�
	bool m_isBumper;		//�׷��� �̰� �ʱ�ȭ�ϱⰡ �������... �������� �浹�ϴº����� ���� �޶����µ�?
	
};

