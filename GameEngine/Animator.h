#pragma once
#include <unordered_map>
#include <string>

#include "ElementBase.h"
#include "../DirectY/Sprite.h"	//Motion
#include "InputManager.h"	//keyinput�� ���� ��� ������ ���� ���

/// <summary>
/// �ִϸ��̼��� �̷�� Motion Ŭ������ �����ϰ� ����� Ŭ����
/// 2023.08.01 ���¿�
/// </summary>
class Animator : public ElementBase
{
public:
	Animator();
	~Animator();

	virtual void Init() override;

	virtual void FixedUpdate() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;

	virtual void PreRender() override;
	virtual void Render(DirectY* directY) override;
	virtual void PostRender(DirectY* directY) override;

	virtual void Release() override;

	virtual ElementType GetElementType() const override;

	virtual GameObject* GetGameObject() const override;
	virtual void SetGameObject(GameObject* gameObject) override;

	//����� �߰��Ѵ�
	void AddMotion(std::string motionName, Graphics::Motion* motion);
	//���� ����� �����Ѵ�
	void SetCurrentMotion(std::string motionName) { m_currentMotion = motionName; }
	//����� �޾ƿ´� - const ���� [] �Ƚ���
	Graphics::Motion* GetMotion(const std::string key)/*const*/ { return m_motionMap[key]; }


	float GetTotalTime() const { return m_totalTime; }
	void SetTotalTime(float val) { m_totalTime = val; }

	float GetDelayTime() const { return m_delayTime; }
	void SetDelayTime(float val) { m_delayTime = val; }
private:
	std::unordered_map<std::string, Graphics::Motion*> m_motionMap;
	std::string m_currentMotion;
	int m_motionIndex;

	// gyu code
	float m_totalTime = 0;
	float m_delayTime = 0.2f;
};

