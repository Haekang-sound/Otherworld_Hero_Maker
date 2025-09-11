#pragma once
class DataControl
{
public:
	DataControl();
	~DataControl();

public:

	void SaveSpriteData(const CString& filePath);
	void LoadSpriteData(const CString& filePath);

	void SaveAnimationData(const CString& filePath);
	void LoadAnimationData(const CString& filePath);

	// 하나의 애니메이션만 저장. 이 경우 로드는 구현 안 할듯.
	void SaveAnimationOneData(const CString& filePath, int idx);

public:

	/// TODO :  Main Doc 파일에서 옮겨와야 함.

	// 메인 뷰에 보이는 스프라이트
	Sprite* m_mainSprite = nullptr;

	// 애니메이션 뷰에 보이는 스프라이트
	Sprite* m_animationViewSprite = nullptr;

	// 메인 스프라이트의 이름
	std::wstring m_mainSpriteName = {};
	// 추출한 스프라이트들
	std::vector<ExtractedSprite*> m_extractedSprites = {};
	// 메인 뷰의 렌더 타겟
	CRenderTarget* m_rt = nullptr;
	// 여러 스프라이트들을 저장할 용도로 만들긴 했는데 사실 잘 사용안해서 나중에 리팩토링해야 함
	std::unordered_map<std::wstring, Sprite*> m_sprites = {};

	// 메인 뷰 클래스 (메인 이미지가 보이는)
	class CGyunityView* m_mainView = nullptr;

	// 스프라이트의 정보를 보여줄 뷰 클래스
	class SpriteInfoView* m_spriteInfoView = nullptr;

	// 다중 선택
	std::queue<ExtractedSprite*> m_selectedBoxQueue;

	// 애니메이션 리스트
	std::vector<class SpriteAnimation*> m_animations = {};
	void ClearAnimations();
	// end my code
};

