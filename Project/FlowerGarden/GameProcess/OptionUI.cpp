#include "OptionUI.h"
#include "Slider.h"
#include "Transform.h"
#include "SoundManager.h"
#include "GameObject.h"

OptionUI::OptionUI(Slider* masterVolumeSlider, Slider* BGMVolumeSlider, Slider* SFXVolumeSlider)
	: m_masterVolumeSlider(masterVolumeSlider),
	m_BGMVolumeSlider(BGMVolumeSlider),
	m_SFXVolumeSlider(SFXVolumeSlider),
	m_myTransform(nullptr),
	m_volumeRatio(0)
{
	
}

OptionUI::~OptionUI()
{
	delete UISprite;
}

void OptionUI::Init()
{
	m_myTransform = ((Transform*)m_gameObject->GetElement(ElementType::Transform));

	// �����̴����� �ʱ�ȭ�� ����
	m_masterVolumeSlider->Init();
	m_BGMVolumeSlider->Init();
	m_SFXVolumeSlider->Init();

	m_gameObject->SetIsDraw(false);
	//m_gameObject->SetActive(m_gameObject->GetActive());

}

void OptionUI::FixedUpdate()
{

}

void OptionUI::Update(float deltaTime)
{

	//m_myTransform->SetLocalPosition({ 100,100 });

	SoundManager::GetInstance().MasterGroupVolume(m_masterVolumeSlider->m_areaRatio);
	SoundManager::GetInstance().ChannelGroupVolume(ChannalGroups::BGM, m_BGMVolumeSlider->m_areaRatio);
	SoundManager::GetInstance().ChannelGroupVolume(ChannalGroups::SFX, m_SFXVolumeSlider->m_areaRatio);
	SoundManager::GetInstance().ChannelGroupVolume(ChannalGroups::UI, m_SFXVolumeSlider->m_areaRatio);

}

void OptionUI::LateUpdate()
{

}

void OptionUI::PreRender()
{

}

void OptionUI::Render(DirectY* directY)
{
	directY->DrawBitmap(UISprite);
	directY->DrawTextW(L"������",10, 100, 30);
	directY->DrawTextW(L"ȿ����",10, 200, 30);
	directY->DrawTextW(L"�����",10, 300, 30);

}

void OptionUI::PostRender()
{
	
}

void OptionUI::Release()
{

}

ElementType OptionUI::GetElementType() const
{
	return ElementType::Script;
}

GameObject* OptionUI::GetGameObject() const
{
	return m_gameObject;
}

void OptionUI::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

void OptionUI::SetVolumeRatio(float ratio)
{
	SoundManager::GetInstance().MasterGroupVolume(ratio);
}

void OptionUI::SetDraw()
{
	m_gameObject->SetIsDraw(false);
	m_gameObject->SetActive(false);
}
