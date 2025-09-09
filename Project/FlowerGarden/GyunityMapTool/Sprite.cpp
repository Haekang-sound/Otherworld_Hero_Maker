#include "pch.h"
#include "Sprite.h"
#include "Global.h"
Sprite::Sprite()
{

}

Sprite::~Sprite()
{
	delete m_d2dBitmap;
}

void Sprite::Render(CRenderTarget* renderTarget)
{
	
	m_d2dBitmap;
	CD2DSizeF size = m_d2dBitmap->GetSize();
	CD2DRectF rectangle(0, 0, size.width, size.height);


	// 여기 카메라 작업 중. 
	//renderTarget->SetTransform(g_CameraPos * D2D1::Matrix3x2F::Translation(Pos.x, Pos.y));
	
// 	renderTarget->SetTransform(
// 		D2D1::Matrix3x2F::Scale(g_Scale, g_Scale) *
// 		g_CameraPos *
// 		D2D1::Matrix3x2F::Translation(Pos.x, Pos.y)
// 	);
	renderTarget->SetTransform(
		g_CameraPos *
		D2D1::Matrix3x2F::Translation(Pos.x, Pos.y)
		* D2D1::Matrix3x2F::Scale(g_Scale, g_Scale) 
	);

	renderTarget->DrawBitmap(m_d2dBitmap, &rectangle, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &rectangle);
	//renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}
