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

	// �ϳ��� �ִϸ��̼Ǹ� ����. �� ��� �ε�� ���� �� �ҵ�.
	void SaveAnimationOneData(const CString& filePath, int idx);

public:

	/// TODO :  Main Doc ���Ͽ��� �Űܿ;� ��.

	// ���� �信 ���̴� ��������Ʈ
	Sprite* m_mainSprite = nullptr;

	// �ִϸ��̼� �信 ���̴� ��������Ʈ
	Sprite* m_animationViewSprite = nullptr;

	// ���� ��������Ʈ�� �̸�
	std::wstring m_mainSpriteName = {};
	// ������ ��������Ʈ��
	std::vector<ExtractedSprite*> m_extractedSprites = {};
	// ���� ���� ���� Ÿ��
	CRenderTarget* m_rt = nullptr;
	// ���� ��������Ʈ���� ������ �뵵�� ����� �ߴµ� ��� �� �����ؼ� ���߿� �����丵�ؾ� ��
	std::unordered_map<std::wstring, Sprite*> m_sprites = {};

	// ���� �� Ŭ���� (���� �̹����� ���̴�)
	class CGyunityView* m_mainView = nullptr;

	// ��������Ʈ�� ������ ������ �� Ŭ����
	class SpriteInfoView* m_spriteInfoView = nullptr;

	// ���� ����
	std::queue<ExtractedSprite*> m_selectedBoxQueue;

	// �ִϸ��̼� ����Ʈ
	std::vector<class SpriteAnimation*> m_animations = {};
	void ClearAnimations();
	// end my code
};

