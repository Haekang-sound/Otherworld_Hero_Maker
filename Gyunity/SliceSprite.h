#pragma once
#include <afx.h>
class SliceSprite : public CObject
{
public:
	SliceSprite();
	SliceSprite(float l, float t, float r, float b);
	virtual ~SliceSprite();

	void Render(CRenderTarget* renderTarget, CD2DSolidColorBrush* brush);

	float Left, Top, Right, Bottom;
	float PivotX, PivotY;
};

