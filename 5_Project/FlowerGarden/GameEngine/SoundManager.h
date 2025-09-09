#pragma once
// �̱��� ���ø��� ����ϱ� ���� ���
#include "Singleton.h"
#include <string>
#include <iostream>
// FMOD ���
#include "../core/inc/fmod.hpp"

#include <functional>

#if x86
#pragma comment (lib,"../core/lib/x86/fmod_vc.lib")
#else
#pragma comment (lib,"../core/lib/x6/fmod_vc.lib")
#endif

enum ChannalGroups
{
	MASTER,
	UI,
	BGM,
	Narr,
	SFX,
};

enum class PlayType
{
	UI,
	BGM,
	NARR,
	SFX,
};

enum FADE
{
	NONE,
	FADE_IN,
	FADE_OUT,
};


/// <summary>
/// ���带 �����ϰ� ����Ѵ�.
/// </summary>
class SoundManager : public Singleton<SoundManager>
{
public:

	///  �ʼ��ڵ�
	void Init();
	void Update();

	/// ���ÿ�
	void SetChannelGroup();

	/// get
	// ���� ����ҽ��� �����մϴ�
	FMOD::Sound* GetCurrentSound() { return m_sound; }

	/// load
	FMOD::Sound* LoadSound(std::string _path);

	/// ���
	void PlayBack(FMOD::Sound* _sound, float _volume = 1.f, PlayType _type = PlayType::SFX, FMOD_MODE mode = FMOD_LOOP_OFF, int loopCount = 0);

	// �Ͻ�����
	void PauseSound();
	void PauseSound(FMOD::Sound* targetSound);

	// �Ͻ����� ����
	void PauseSoundPlay();
	void PauseSoundPlay(FMOD::Sound* targetSound);

	// ����
	void StopSound(/*���� ���*/);
	void StopSound(FMOD::Sound* targetSound);
	void StopChannelGroup(ChannalGroups channelgroup);
	
	// FadeIn/Out
	void FadeIn(FMOD::Sound* targetSound, int fTime);
	void FadeOut(FMOD::Sound* targetSound, int fTime);

	// pitchShift
	void SetBGMPitch(float pitch);
	void SetPitch(FMOD::Sound* targetSound, float speed);

	// ä�α׷캼�� ����
	void ChannelGroupVolume(ChannalGroups _channelGroup,float _volume);
	float GetChannelGroupVolume(ChannalGroups _channelGroup);
	void MasterGroupVolume(float _volume);

	// ��������� Ȯ���Ѵ�.
	bool IsPlaying(FMOD::Sound* targetSound);

private:
	SoundManager()
		: m_system(nullptr),
		version(0),
		m_sound(nullptr),
		m_result(), m_isPlaying(false),
		ui_index(0), bgm_index(8), narr_index(16), sfx_index(24),
		m_channels{}, m_ChannelGroup{},
		m_reverb(nullptr), tempSound(nullptr)
	{}

	~SoundManager() {}

private:
	FMOD::System* m_system;
	FMOD_RESULT m_result;

	/// �����긦 ������? 
	void TestReverb();

	FMOD::Reverb3D* m_reverb;
	FMOD_VECTOR m_rVector = {0.f, 0.f, 0.f};
	float minDistance = 0;
	float maxDistance = 100;
	FMOD_REVERB_PROPERTIES m_properties = FMOD_PRESET_ARENA;

	// ä��
	const int chNum = 64;
	FMOD::Channel* m_channels[64];
	// bgm[8] ui[8] Narr[8] 2sfx[16]

	// ����
	FMOD::Sound* m_sound;
	bool m_isPlaying;
	unsigned int version;

	friend class Singleton<SoundManager>;

	/// ������
	FMOD::ChannelGroup *m_ChannelGroup[5];

	int ui_index;
	int bgm_index;
	int narr_index;
	int sfx_index;

	/// �ӽ������ ����
	FMOD::Sound* tempSound;

	unsigned long long dspclock = 0;
	int rate = 0;
};