#include "pch.h"
#include "SliceSprite.h"

SliceSprite::SliceSprite()
	: Left(0), Top(0), Right(0), Bottom(0) ,PivotX(0), PivotY(0)
{

}

SliceSprite::SliceSprite(float l, float t, float r, float b)
	: Left(l), Top(t), Right(r), Bottom(b)
{

}

SliceSprite::~SliceSprite()
{

}

void SliceSprite::Render(CRenderTarget* renderTarget, CD2DSolidColorBrush* brush)
{
	renderTarget->DrawRectangle(CD2DRectF(Left, Top, Right, Bottom), brush);
}
