#include "SoundManager.h"
#include <windows.h>

/// <summary>
/// FMOD�ʱ�ȭ �Լ�, �ý����� �����Ѵ�.
/// </summary>
void SoundManager::Init()
{
	// System_Create, FMOD �ν��Ͻ� ����

	m_result = FMOD::System_Create(&m_system);
	if (m_result != FMOD_OK) return;
	// init, FMOD�ʱ�ȭ
	m_result = m_system->init(64, FMOD_INIT_NORMAL, 0);  // �ý��� �ʱ�ȭ : chaneel 32������ ����ϰڴ�.
	if (m_result != FMOD_OK) return;
	// �ʿ��� �ʱ�ȭ�� ���̴�

	// ���� fmod ����
	m_system->getVersion(&version);
	TestReverb();

	SetChannelGroup();

}

/// <summary>
/// update�� ���û����� �ƴϴ�
/// �ݵ�� �Ͼ���ϴ� �����̴�
/// FMOD �ý����� ������Ʈ�մϴ�.
/// �̰��� '����' ƽ�� �� �� �Ǵ� ���ø����̼��� �����Ӵ� �� �� ȣ��Ǿ�� �մϴ�.
/// </summary>
void SoundManager::Update()
{
	m_result = m_system->update();
	if (m_result != FMOD_OK) return;
	// ���÷���Ʈ�� �����´�
	// Ÿ�ӸŴ����� ������ ��� ����������? 
	m_system->getSoftwareFormat(&rate, 0, 0);
}

/// <summary>
/// ���������� ��θ� �Է� �ް�
/// �������� �ʴ� ���������͸� ��ȯ�ϴ� �Լ�
/// </summary>
/// <param name="soundPath">�������� ���</param>
/// <returns></returns>
FMOD::Sound* SoundManager::LoadSound(std::string _path)
{
	// wav ���Ϸκ��� sound ����
	m_result = m_system->createSound(/*"jaguar.wav"*/_path.c_str(), FMOD_DEFAULT, 0, &m_sound);
	if (m_result == FMOD_OK)
	{
		return m_sound;
	}
	std::cout << "�߸��� ����Դϴ�" << std::endl;
	return nullptr;
}

/// <summary>
/// ���带 ����ϴ� �Լ�
/// default���� SFX�� �Ѵ�.
/// 
/// ��� ������ ���带 ����ϴ� �÷��̹� �Լ�
/// 1. �׷캰�� ä���� ��ȸ�ϸ� ����Ѵ�
/// 2. ä�κ��� ���� ������ ����
/// 
/// </summary>
/// <param name="_sound">���� ��ü</param>
/// <param name="_volume">�Ҹ� ũ��</param>
/// <param name="_type">�÷���Ÿ��
/// </param>
void SoundManager::PlayBack(FMOD::Sound* _sound, float _volume, PlayType _type, FMOD_MODE mode, int loopCount)
{
	switch (_type)
	{
	case (PlayType::UI):
	{
		/// ���� ä���� ��������� Ȯ���ϰ� ����ϰ� �ִٸ� ����
		m_channels[ui_index]->isPlaying(&m_isPlaying);
		if (m_isPlaying)
		{
			m_channels[ui_index]->stop();
		}
		//m_channels[ui_index]->addFadePoint(dspclock, 1.0f);
		// ���� ��� ����
		_sound->setMode(mode);
		// ���� �Ͻ�����
		m_result = m_system->playSound(_sound, m_ChannelGroup[UI], true, &m_channels[ui_index]);
		if (m_result != FMOD_OK) return;
		// ��������
		m_channels[ui_index]->setVolume(_volume);
		// ���� ���
		m_channels[ui_index]->setPaused(false);
		
		///��ȸ����� ����
		ui_index = (ui_index++) % 8;
		break;
	}
	case(PlayType::BGM):
	{

		/// ���� ä���� ��������� Ȯ���ϰ� ����ϰ� �ִٸ� ����
		m_channels[bgm_index]->isPlaying(&m_isPlaying);
		if (m_isPlaying)
		{
			m_channels[bgm_index]->stop();
		}
		//m_channels[bgm_index]->addFadePoint(dspclock, 1.0f);

		// ���� ��� ����
		_sound->setMode(FMOD_LOOP_NORMAL);
		// ���� �Ͻ�����
		m_result = m_system->playSound(_sound, m_ChannelGroup[BGM], true, &m_channels[bgm_index]);
		if (m_result != FMOD_OK) return;
		// ��������
		m_channels[bgm_index]->setVolume(_volume);
		// ���� ���
		m_channels[bgm_index]->setPaused(false);
		
		///��ȸ����� ����
		bgm_index = (bgm_index++) % 8 + 8;
		break;
	}
	case (PlayType::NARR):
	{
		/// ���� ä���� ��������� Ȯ���ϰ� ����ϰ� �ִٸ� ����
		m_channels[narr_index]->isPlaying(&m_isPlaying);
		if (m_isPlaying)
		{
			m_channels[narr_index]->stop();
		}
		//m_channels[narr_index]->addFadePoint(dspclock, 1.0f);
		// ���� ��� ����
		_sound->setMode(mode);
		// ���� �Ͻ�����
		m_result = m_system->playSound(_sound, m_ChannelGroup[Narr], true, &m_channels[narr_index]);
		if (m_result != FMOD_OK) return;
		// ��������
		m_channels[narr_index]->setVolume(_volume);
		// ���� ���
		m_channels[narr_index]->setPaused(false);

		///��ȸ����� ����
		narr_index = (narr_index++) % 8 + 16;
		break;
	}
	case(PlayType::SFX):
	{
		/// ���� ä���� ��������� Ȯ���ϰ� ����ϰ� �ִٸ� ����
		m_channels[sfx_index]->isPlaying(&m_isPlaying);
		if (m_isPlaying)
		{
			m_channels[sfx_index]->stop();
		}
		//m_channels[sfx_index]->addFadePoint(dspclock, 1.0f);

		// ���� ��� ����
		_sound->setMode(mode);
		// ���� �Ͻ�����
		m_result = m_system->playSound(_sound, m_ChannelGroup[SFX], true, &m_channels[sfx_index]);
		if (m_result != FMOD_OK) return;
		// ��������
		m_channels[sfx_index]->setVolume(_volume);

		m_channels[sfx_index]->setPaused(false);
		m_channels[sfx_index]->setLoopCount(loopCount);
				
		sfx_index = (sfx_index++) % 8 + 24;
		break;
	}
	default:
		break;
	}

}

// ���ä���� �Ͻ������Ѵ�.
// ä��, ä�α׷��� �迭�� ����� �ݺ������� �������� ������
void SoundManager::PauseSound()
{
	for (int i = 0; i < chNum; i++)
	{
		m_channels[i]->setPaused(true);
	}
}

void SoundManager::PauseSound(FMOD::Sound* targetSound)
{
	for (int i = 0; i < chNum; i++)
	{
		m_channels[i]->getCurrentSound(&tempSound);
		if (tempSound == targetSound)
		{
			m_channels[i]->setPaused(true);
		}
	}
	tempSound = nullptr;
}


// ���ä���� �Ͻ������Ѵ�.
// ä��, ä�α׷��� �迭�� ����� �ݺ������� �������� ������
void SoundManager::PauseSoundPlay(/*�Ͻ����� ���*/)
{
	for (int i = 0; i < chNum; i++)
	{
		m_channels[i]->setPaused(false);
	}
}


void SoundManager::PauseSoundPlay(FMOD::Sound* targetSound)
{
	for (int i = 0; i < chNum; i++)
	{
		m_channels[i]->getCurrentSound(&tempSound);
		if (tempSound == targetSound)
		{
			m_channels[i]->setPaused(false);
		}
	}
	tempSound = nullptr;
}

/// <summary>
/// �����Ѵ�.
/// </summary>
void SoundManager::StopSound(/*���� ���*/)
{
	for (int i = 0; i < chNum; i++)
	{
		m_channels[i]->stop();
	}

}

void SoundManager::StopSound(FMOD::Sound* stopSound)
{
	for (int i = 0; i < chNum; i++)
	{
		m_channels[i]->getCurrentSound(&tempSound);
		if( tempSound ==  stopSound)
		{
			m_channels[i]->stop();
		}
	}
	tempSound = nullptr;
}

void SoundManager::StopChannelGroup(ChannalGroups channelgroup)
{
	m_ChannelGroup[channelgroup]->stop();
}

void SoundManager::FadeIn(FMOD::Sound* targetSound, int fTime)
{
	for (int i = 0; i < chNum; i++)
	{
		m_channels[i]->getCurrentSound(&tempSound);
		if (tempSound == targetSound)
		{
			m_channels[i]->getDSPClock(0, &dspclock);
			m_channels[i]->addFadePoint(dspclock, 0.0f);
			m_channels[i]->addFadePoint(dspclock + ((unsigned long long)rate * fTime), 1.0f);
		}
	}
	tempSound = nullptr;
}

void SoundManager::FadeOut(FMOD::Sound* targetSound, int fTime)
{
	for (int i = 0; i < chNum; i++)
	{
		m_channels[i]->getCurrentSound(&tempSound);
		if (tempSound == targetSound)
		{
			m_channels[i]->getDSPClock(0, &dspclock);		// ���� dspclock�� ������
			m_channels[i]->addFadePoint(dspclock, 1.0f);	// (�ð�, ����) ,, ������ �ð��� ������ �����Ѵ�.
			m_channels[i]->addFadePoint(dspclock + ((unsigned long long)rate * fTime), 0.0f);    // 
			m_channels[i]->setDelay(0, dspclock + ((unsigned long long)rate * fTime), true);     // ���۽ð�, ����ð�, true==stop false == pause
		}
	}
	tempSound = nullptr;
}

void SoundManager::SetBGMPitch(float pitch)
{
	for (int i = 8; i < 16; i++)
	{
		m_channels[i]->isPlaying(&m_isPlaying);
		if (m_isPlaying)
		{
			m_channels[i]->setPitch(pitch);

		}
	}
}

void SoundManager::SetPitch(FMOD::Sound* targetSound, float speed)
{
	for (int i = 0; i < chNum; i++)
	{
		m_channels[i]->getCurrentSound(&tempSound);
		if (tempSound == targetSound)
		{
			m_channels[i]->setPitch(speed);
		}
	}
	tempSound = nullptr;
}

/// <summary>
/// ä�α׷��� ������ �����ϴ� �Լ�
/// </summary>
/// <param name="_channelGroup">ä���� �����Ѵ�.</param>
/// <param name="_volume">������ �����Ѵ�.</param>
void SoundManager::ChannelGroupVolume(ChannalGroups _channelGroup, float _volume)
{
	if (_volume >= 1)
	{
		_volume = 1;
	}
	else if(_volume <= 0)
	{
		_volume = 0;
	}
	m_ChannelGroup[_channelGroup]->setVolume(_volume);
}

float SoundManager::GetChannelGroupVolume(ChannalGroups _channelGroup)
{
	float volume;
	m_ChannelGroup[_channelGroup]->getVolume(&volume);
	return volume;
}

void SoundManager::MasterGroupVolume(float _volume)
{
	m_ChannelGroup[MASTER]->setVolume(_volume);
}

bool SoundManager::IsPlaying(FMOD::Sound* targetSound)
{
	for (int i = 0; i < chNum; i++)
	{
		m_channels[i]->getCurrentSound(&tempSound);
		if (tempSound == targetSound)
		{
			return true;
		}
	}
	return false;
}

void SoundManager::TestReverb()
{
	//1 ������ ��ü�� �����Ѵ�.
	m_system->createReverb3D(&m_reverb);
	//2 ������ �ɼ��� �����Ѵ�.
	m_reverb->setProperties(&m_properties);
	//3
	m_reverb->release();
	//m_reverb->set3DAttributes(&m_rVector, minDistance, maxDistance);

}

void SoundManager::SetChannelGroup()
{
	// ������ ä�� ����
	m_system->getMasterChannelGroup(&m_ChannelGroup[MASTER]);

	// ä�α׷��� ����

	m_system->createChannelGroup("UIGroup", &m_ChannelGroup[UI]);
	m_system->createChannelGroup("BGMGroup", &m_ChannelGroup[BGM]);
	m_system->createChannelGroup("NarrGroup", &m_ChannelGroup[Narr]);
	m_system->createChannelGroup("SFXGroup", &m_ChannelGroup[SFX]);

	// ä�� ���� �׷�����
	int i = 0;
	for (; i < 8; i++)
	{
		m_channels[i]->setChannelGroup(m_ChannelGroup[UI]);
		m_channels[i]->setPriority(0);
	}
	for (; i < 16; i++)
	{
		m_channels[i]->setChannelGroup(m_ChannelGroup[BGM]);
		m_channels[i]->setPriority(10);
	}
	for (; i < 24; i++)
	{
		m_channels[i]->setChannelGroup(m_ChannelGroup[Narr]);
		m_channels[i]->setPriority(20);
	}

	for (; i < 32; i++)
	{
		m_channels[i]->setChannelGroup(m_ChannelGroup[SFX]);
		m_channels[i]->setPriority(30);
	}

}

