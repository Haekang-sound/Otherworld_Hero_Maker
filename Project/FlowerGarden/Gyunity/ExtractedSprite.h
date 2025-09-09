#pragma once
#include <afx.h>
class ExtractedSprite : public CObject
{
public:
	ExtractedSprite();
	ExtractedSprite(float l, float t, float r, float b, float pivotX, float pivotY);
	virtual ~ExtractedSprite();

	void Render(CRenderTarget* renderTarget);

	std::wstring Name;

	float Left, Top, Right, Bottom;

	// 피봇의 기준은 0 ~ 1 사이의 비율로 결정
	float PivotX, PivotY;

	bool Selected;

};

