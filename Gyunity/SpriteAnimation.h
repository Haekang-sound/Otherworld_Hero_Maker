#pragma once
class SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();

public:
	std::wstring m_name;

	// �ִϸ��̼� ������ ���� (1000�� 1��)
	int m_delayTime = 100;
	std::vector<ExtractedSprite*> m_sprites;
};

