#pragma once
class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	CD2DBitmap* GetSprite() { return m_d2dBitmap; }

	void SetBitmap(CD2DBitmap* bitmap) { m_d2dBitmap = bitmap; m_bitmapSize = bitmap->GetSize(); }
	CD2DBitmap* GetBitmap() { return m_d2dBitmap; }

	void Render(CRenderTarget* renderTarget);

	Vector2 Pos;

	CD2DSizeF GetSize() { return m_bitmapSize; }
protected:
	CD2DBitmap* m_d2dBitmap;
	CD2DSizeF m_bitmapSize;

	//D2D1::Matrix3x2F m_mat = D2D1::Matrix3x2F::Identity();
};

