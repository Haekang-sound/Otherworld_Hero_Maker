#include "pch.h"
#include "ExtractedSprite.h"

ExtractedSprite::ExtractedSprite()
	: Left(0), Top(0), Right(0), Bottom(0), PivotX(0), PivotY(0), Selected(false)
{

}

ExtractedSprite::ExtractedSprite(float l, float t, float r, float b, float pivotX, float pivotY)
	: Left(l), Top(t), Right(r), Bottom(b), PivotX(pivotX), PivotY(pivotY), Selected(false)
{

}

ExtractedSprite::~ExtractedSprite()
{

}

void ExtractedSprite::Render(CRenderTarget* renderTarget)
{
	D2D1::ColorF c  = D2D1::ColorF::Green;
	if (Selected)
		c = D2D1::ColorF::Red;
	else
		c = D2D1::ColorF::Green;

	CD2DSolidColorBrush* tempBrush = new CD2DSolidColorBrush(
		renderTarget,
		D2D1::ColorF(c)
	);
	CD2DSolidColorBrush* tempBrush2 = new CD2DSolidColorBrush(
		renderTarget,
		D2D1::ColorF(D2D1::ColorF::Blue)
	);


	// »óÀÚ render
	renderTarget->DrawRectangle(CD2DRectF(Left, Top, Right, Bottom), tempBrush);

	// pivot render
	float pivotPosX = Left + abs(Right - Left) * PivotX;
	float pivotPosY = Top + abs(Bottom - Top) * PivotY;
	
	//float pivotXPos = 
	renderTarget->DrawRectangle(CD2DRectF(pivotPosX - 2, pivotPosY - 2, pivotPosX+ 2, pivotPosY + 2), tempBrush2);




	tempBrush->Destroy();
	tempBrush = nullptr;
	tempBrush2->Destroy();
	tempBrush2 = nullptr;
}
