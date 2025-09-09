#pragma once
class BitmapUtils
{
public:
	static void ExtractedSprites(HDC hdc, COLORREF& keyColor, Sprite* sourceSprite);
	//void ExtractRects(Sprite* sprite, std::vector<D2D1_RECT_F>& outRects);
	//void ExtractRectsFromSprites(Sprite* sprite, std::vector< D2D1_RECT_F>& outRects);
};

