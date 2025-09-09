#pragma once
#include <ElementBase.h>
#include "../DirectY/DirectY.h"
#include "GameEngine.h"
#include "Transform.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "AudioSource.h"


class GameEngine;
class DirectY;

/// <summary>
/// Ÿ�̸� 
/// </summary>
class Timer : public ElementBase
{
public:
	Timer(GameEngine* gameEngine, DirectY* directY);
	~Timer();

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

	/*--------------------------------------------------------------------*/
	
	void ResetTimer(float settingTime = 120.f) { m_nowTime = settingTime; }
	void PlusTimer(float plusTime = 0.f) { m_nowTime += plusTime; }
	void MinustTimer(float minusTime = 0.f) { m_nowTime -= minusTime; }

	/*--------------------------------------------------------------------*/
	
	bool IsTimerON() { return m_timerState; }
	bool StartTimer() { m_timerState = true; return m_timerState; }
	bool StopTimer() { m_timerState = false; return m_timerState; }

	/*--------------------------------------------------------------------*/
	float GetNowTime() { return m_nowTime; }

	/*--------------------------------------------------------------------*/
	void SetAudioSource(AudioSource* audioSource) { m_audioSource = audioSource; }

private:
	// Ÿ�̸Ӱ� �����־�� �ϴ°� ?
	// Ÿ�̸Ӵ� �ð��� �ø��°Ծƴ϶� 
	// �־��� �ð����� �����ϴ� ����� ����ϴ� ���� ���������𸣰ڴ�. 
	
	// ��ħ ����� ���� ��Ʈ�� ����
	Graphics::Sprite* m_secondHand;
	ID2D1Bitmap* m_secondHandBitmap;
	GameEngine* m_gameEngine;
	DirectY* m_directY;

	AudioSource* m_audioSource;

	bool m_timerState;

	bool m_isPlaying;
	bool m_isPlayingFast;

	float m_baseTime;
	float m_nowTime;
	float m_sumTime;

	float m_degree;

};

