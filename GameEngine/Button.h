#pragma once
#include "ElementBase.h"
#include <functional>

namespace Graphics { struct Sprite; }
namespace Graphics { class Motion; }
class AudioSource;

enum class ButtonState
{
	Normal,		// �⺻
	Pressed,	// ����
	Selected,	// ���콺�� ���� ����
	Disabled	// ��ȣ �ۿ� x
};

template <typename ReturnType, typename ParameterType>
class EventFuction
{
	std::function<ReturnType(ParameterType)> m_function;
};

class Button : public ElementBase
{
public:
	Button(int left, int top, int right, int bottom); // �ʺ�, ���� �߽���
	~Button(); 

	/// Element Override
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

	// Ŭ�� ���� �� ������ ���� (�̸� ���ٷ� ����ص� ���� ����)
	void OnClick();
	void OnPressed();	// ������ ��

	void SetDisabled() { m_buttonState = ButtonState::Disabled; }
	void SetEnable() { m_buttonState = ButtonState::Normal; }

	void SetOnClick(std::function<void(void)> onClick);
	void SetOnPressed(std::function<void(void)> onPress);

//	void OnNormal();	// ��� ����
//	void OnSelected();	// ���콺�� ���� ����
//	void OnDisabled();	// ��ȣ�ۿ� �ȵ� ��

	//test
	Graphics::Sprite* m_sprite;
	void SetAudioSource(AudioSource* audioSource) { m_audioSource = audioSource; }

private:
	// ��ư ���� - circle, ellipse ����� ��ư�� �ʿ��ұ�
	int m_left;
	int m_right;
	int m_top;
	int m_bottom;

	std::function<void(void)> m_onClick;
	std::function<void(void)> m_onPress;

	// ����ؾ� �� ���� ���� Get, Set ������ֱ�
	ButtonState m_buttonState;
	AudioSource* m_audioSource;
	

	
};