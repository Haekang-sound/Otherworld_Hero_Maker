#pragma once
class SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();

public:
	std::wstring m_name;

	// 애니메이션 사이의 간격 (1000당 1초)
	int m_delayTime = 100;
	std::vector<ExtractedSprite*> m_sprites;
};

