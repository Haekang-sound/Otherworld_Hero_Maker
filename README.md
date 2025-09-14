
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/ad7f6a6a-d1e1-487f-9bfb-2509b38a45f0" />

# 자체 엔진 프로젝트 : 이세계 용사 메이커 (Otherworld Hero Maker)

실행환경 : 86x, (Debug/Release)\
실행파일 : FlowerGarden.sln\
게임영상 : https://youtu.be/avXhfSrf8Zw

## 1. 프로젝트 개요
"이세계 용사 메이커"는 C++과 D2D를 기반으로 구축된 자체 엔진을 사용하여 개발한 2D 아이소메트릭뷰 게임입니다. 플레이어는 제한 시간 안에 트럭을 운전하여 도시를 돌아다니는 '용사 후보'들을 쳐서 이세계로 보내야 하는 컨셉을 가지고 있습니다. 
이 프로젝트에서 저는 사운드, 매니저/컴포넌트와 각종 컨텐츠를 맡아 제작하였습니다.

## 2. 기술설명
  ### 2.1 사운드 시스템 구축 (FMOD 라이브러리 활용)
게임의 동적인 재미를 더하기 위해 FMOD 라이브러리를 기반으로 중앙 사운드 관리 시스템인 SoundManager를 구축했습니다.
```c
class SoundManager : public Singleton<SoundManager>
{
public:
  ...	
	/// get
	// 현재 사운드소스를 리턴합니다
	FMOD::Sound* GetCurrentSound() { return m_sound; }

	/// load
	FMOD::Sound* LoadSound(std::string _path);

	/// 재생
	void PlayBack(FMOD::Sound* _sound, float _volume = 1.f, PlayType _type = PlayType::SFX, FMOD_MODE mode = FMOD_LOOP_OFF, int loopCount = 0);

	// 일시정지
	void PauseSound();
	void PauseSound(FMOD::Sound* targetSound);

	// 일시정지 해제
	void PauseSoundPlay();
	void PauseSoundPlay(FMOD::Sound* targetSound);

	// 정지
	void StopSound(/*멈춤 대상*/);
	void StopSound(FMOD::Sound* targetSound);
	void StopChannelGroup(ChannalGroups channelgroup);
	
	// FadeIn/Out
	void FadeIn(FMOD::Sound* targetSound, int fTime);
	void FadeOut(FMOD::Sound* targetSound, int fTime);

	// pitchShift
	void SetBGMPitch(float pitch);
	void SetPitch(FMOD::Sound* targetSound, float speed);

	// 채널그룹볼륨 제어
	void ChannelGroupVolume(ChannalGroups _channelGroup,float _volume);
	float GetChannelGroupVolume(ChannalGroups _channelGroup);
	void MasterGroupVolume(float _volume);

	// 재생중인지 확인한다.
	bool IsPlaying(FMOD::Sound* targetSound);

...
	// 채널
	const int chNum = 64;
	FMOD::Channel* m_channels[64];
	// bgm[8] ui[8] Narr[8] 2sfx[16]

	// 사운드
	FMOD::Sound* m_sound;
	bool m_isPlaying;
	unsigned int version;
};
```

문제 해결 중심의 개발: 개발 초기, 사운드를 반복 재생할 때마다 메모리 사용량이 계단식으로 증가하는 메모리 누수를 발견했습니다. 진단 도구를 통해 원인이 반복문 내에서 사운드 객체를 불필요하게 중복 생성하는 데 있음을 파악하고, 생성 로직을 수정하여 문제를 해결했습니다. 또한 여러 효과음이 동시에 재생되지 않는 문제를 겪었으나, 이는 FMOD의 update() 함수를 매 프레임 호출하지 않아 발생한 문제임을 파악하고 해결하며 외부 라이브러리에 대한 깊은 이해를 쌓을 수 있었습니다.

객체 지향적 설계: 사운드 매니저의 기능을 각 게임 오브젝트에서 손쉽게 사용하도록 AudioSource 컴포넌트를 설계했습니다. 이는 사운드 매니저의 복잡한 로직을 캡슐화하여, 개발자가 Play(), Stop()과 같은 간단한 인터페이스만으로 사운드를 제어할 수 있게 하여 코드의 가독성과 유지보수성을 크게 향상시켰습니다.
```c
class AudioSource : public ElementBase
{
public:
	// 사운드를 추가한다.
	void AddSound(std::string soundName);
	void AddSoundVector(std::string soundName);

	// 음원을 재생한다.
	void PlayBack(std::string soundName, float volume = 1.f, FMOD_MODE mode = FMOD_LOOP_OFF);
	void PlayBackVector(int index);
	void LoopPlayBack(std::string soundName);
	void StopSound(std::string soundName);
	void StopChannel(ChannalGroups channelgroup);
	void PauseSound(std::string soundName);
	void PauseSoundPlay(std::string soundName);

	// 피치(스피드)
	void PitchShift(std::string soundName, float speed = 0.1f);
	
	// 페이드인 아웃
	void FadeIn(std::string soundName, int length);
	void FadeOut(std::string soundName, int length);

	// 같은 음원이 재생중인지 확인
	bool isPlaying(std::string soundName);
	bool isPlaying(int index);
};
```

  ### 2.2 포물선 함수 구현
게임의 핵심 재미 요소인 '캐릭터가 차에 치여 날아가는' 장면을 구현하기 위해 수학적 계산에 기반한 물리 효과를 적용했습니다.

이차함수 포물선 공식 적용: 캐릭터의 현재 위치, 궤적의 최고점, 목표 지점 세 좌표를 이용해 이차함수 포물선 궤적을 실시간으로 계산하는 MoveParabolic 함수를 구현했습니다. 이를 통해 매 프레임 자연스럽고 역동적인 움직임을 만들어내어 게임의 타격감과 시각적 재미를 극대화했습니다.
```c
/// <summary>
/// 포물선이동을 위한 함수
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
MathEngine::Vector2 SkinHeadNPC::MoveParabolic(float deltaTime)
{
	// A 계산: 포물선의 중심 X 좌표
	float A = (float)(
		(m_TargetPos.y * (pow(m_myPos.x, 2) - pow(m_topPos.x, 2)) +
		m_topPos.y * (pow(m_TargetPos.x, 2) - pow(m_myPos.x, 2)) +
		m_myPos.y * (pow(m_topPos.x, 2) - pow(m_TargetPos.x, 2)))
		/
		(2 * ((m_TargetPos.y - m_topPos.y) * m_myPos.x +
		 	  (m_myPos.y - m_TargetPos.y) * m_topPos.x +
			  (m_topPos.y - m_myPos.y) * m_TargetPos.x)));
	
	// C 계산: 포물선의 곡률
	float B = (float)(m_myPos.y - m_topPos.y) / (float)((pow(m_myPos.x, 2) - pow(m_topPos.x, 2) + 2 * A * (m_topPos.x - m_myPos.x)));

	// B 계산: 포물선의 Y 절편
	float C = m_topPos.y - (float)(B * pow((m_topPos.x - A), 2));

	m_myPos.x += deltaTime * 200;

	float y = (float)(B * pow((m_myPos.x - A), 2) + C);


	return { m_myPos.x,y };
}
```

  ### 2.3 기타 컨텐츠 구현
타이머 및 UI 시스템: 게임의 핵심 규칙인 '제한 시간'을 관리하기 위해 **Timer**를 구현하였습니다. 또한 이와 연동되는 UI 시스템을 구축하여 플레이어에게 명확한 정보를 제공하도록 했습니다.
