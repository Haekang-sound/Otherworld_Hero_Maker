#include "pch.h"
#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}


void Sprite::ExtractPixelData()
{
	// 비트맵 크기 및 픽셀 형식 가져오기
	D2D1_SIZE_U size = m_d2dBitmap->GetPixelSize();
	D2D1_BITMAP_PROPERTIES props;
	
	m_d2dBitmap->Get()->GetDpi(&props.dpiX,&props.dpiY);

	// 비트맵 데이터를 저장할 메모리 버퍼 생성
	BYTE* buffer = new BYTE[size.width * size.height * 4]; // 4 bytes per pixel (assuming 32-bit RGBA format)

	// ID2D1Bitmap에서 메모리 버퍼로 데이터 복사
	D2D1_RECT_U rect = D2D1::RectU(0, 0, size.width, size.height);
	HRESULT hr = m_d2dBitmap->Get()->CopyFromMemory(&rect, buffer, size.width * 4);

	if (SUCCEEDED(hr))
	{
		// 픽셀 데이터 읽기
		for (UINT y = 0; y < size.height; y++)
		{
			for (UINT x = 0; x < size.width; x++)
			{
				UINT offset = (y * size.width + x) * 4; // 4 bytes per pixel (RGBA)
				BYTE red = buffer[offset];
				BYTE green = buffer[offset + 1];
				BYTE blue = buffer[offset + 2];
				BYTE alpha = buffer[offset + 3];

			}
		}
	}

	// 메모리 누수 방지를 위해 메모리 해제
	delete[] buffer;
}

void Sprite::ExtractRectsFromSprites(HDC hdc, Sprite* sprite, COLORREF& keyColor, std::vector<CD2DRectU>& outRects)
{
// 	CD2DSizeF size = sprite->m_d2dBitmap->GetSize();
// 	std::vector<std::vector<bool>> MaskBitmap(size.height, std::vector<bool>(size.width, false));
// 	
// 	CD2DBitmap* spriteBitmap = sprite->m_d2dBitmap;
// 
// 	for (int Y = 0; Y < size.height; ++Y)
// 	{
// 		for (int X = 0; X < size.width; ++X)
// 		{
// 			if (MaskBitmap[Y][X] == false && GetPixel(hdc,X,Y) != keyColor)
// 			{
// 				CD2DPointF Origin;
// 				CD2DPointF Dimension;
// 
// 				if (HasConnectedRect(hdc,keyColor,X,Y,Origin,Dimension, size.width, size.height))
// 				{
// 					CD2DRectU NewRect({Origin.x, Origin.y,Origin.x + Dimension.x , Origin.y + Dimension.y});
// 					bool hasOverlap = false;
// 					do 
// 					{
// 						hasOverlap = false;
// 						for (int outRectIndex = 0; outRectIndex < outRects.size(); ++outRectIndex)
// 						{
// 							CD2DRectU& ExistingRect = outRects[outRectIndex];
// 							bool bRectsOverlapping = NewRect.right > ExistingRect.left
// 								&& NewRect.left < ExistingRect.right
// 								&& NewRect.bottom > ExistingRect.top
// 								&& NewRect.top < ExistingRect.bottom;
// 
// 							if (bRectsOverlapping)
// 							{
// 								NewRect = CD2DRectU(min(NewRect.left, ExistingRect.left), min(NewRect.top, ExistingRect.top),
// 									max(NewRect.right, ExistingRect.right), max(NewRect.bottom, ExistingRect.bottom));
// 								
// 								outRects.erase(std::find(outRects.begin(), outRects.end(), ExistingRect));
// 								break;
// 							}
// 						}
// 					} while (hasOverlap);
// 					FillRect(MaskBitmap, NewRect.left, NewRect.top, NewRect.right - NewRect.left, NewRect.top - NewRect.bottom);
// 					outRects.push_back(NewRect);
// 				}
// 			}
// 		}
// 	}
}

void Sprite::ExtractRects(Sprite* sprite, std::vector<D2D1_RECT_F>& outRects)
{

}

bool Sprite::HasConnectedRect(HDC hdc, COLORREF& keyColor, const int X, const int Y, CD2DPointF& OutOrigin, CD2DPointF& OutDimension, int Width, int Height)
{
	if (GetPixel(hdc, X, Y) == keyColor)
	{
		// selected an empty pixel
		OutOrigin.x = 0;
		OutOrigin.y = 0;
		OutDimension.x = 0;
		OutDimension.y = 0;

		return false;
	}

	int NumPasses = 0;
	int MaxPasses = 40;
	CD2DPointF Origin(0, 0);
	CD2DPointF Dimension(0, 0);
	CD2DPointF FillPoint(X, Y);

	std::vector<std::vector<bool>> maskBitmap(Height ,std::vector<bool>(Width,false));
	// TODO : temp while true
	do
	{
		//FloodFill
		FloodFill(hdc, keyColor, maskBitmap, X, Y);
		GetTightBounds(hdc, maskBitmap, keyColor, Origin, Dimension);
	} while (NumPasses++ < MaxPasses && HasOverlappingIsland(hdc, maskBitmap, keyColor, Origin, Dimension, FillPoint));

	OutOrigin = Origin;
	OutDimension = Dimension;

	return true;
}

void Sprite::FloodFill(HDC hdc, COLORREF& keyColor, std::vector<std::vector<bool>>& maskBitmap, int startX, int startY)
{
	std::vector<CD2DPointF> QueuedPoints;
	QueuedPoints.reserve(maskBitmap.size());

	QueuedPoints.push_back(CD2DPointF(startX, startY));
	while (QueuedPoints.size() > 0)
	{
		CD2DPointF Point = QueuedPoints.back();
		QueuedPoints.pop_back();
		if (Point.y < 0 || Point.x < 0 || Point.y > maskBitmap.size() - 1 || Point.x > maskBitmap[0].size() - 1) continue;
		if (maskBitmap[Point.y][Point.x] == false && GetPixel(hdc, Point.x, Point.y) != keyColor)
		{
			maskBitmap[Point.y][Point.x] = true;
			if (Point.x > 0)
			{
				QueuedPoints.push_back(CD2DPointF(Point.x - 1, Point.y));
			}
			if (Point.x < maskBitmap.size() - 1)
			{
				QueuedPoints.push_back(CD2DPointF(Point.x + 1, Point.y));
			}
			if (Point.y > 0)
			{
				QueuedPoints.push_back(CD2DPointF(Point.x, Point.y - 1));
			}
			if (Point.y < maskBitmap[0].size() - 1)
			{
				QueuedPoints.push_back(CD2DPointF(Point.x, Point.y + 1));
			}
		}
	}
}

bool Sprite::HasOverlappingIsland(HDC hdc, std::vector<std::vector<bool>> MaskBitmap, COLORREF& keyColor, const CD2DPointF& Origin, const CD2DPointF& Dimension, CD2DPointF& OutFill)
{
	// 방문하지 않은 영역이며, 유효한 색상이라면),
	// OutFill 변수에 해당 위치를 저장하고, true를 반환. 즉, 겹치는 도형이 있다는 것을 의미
	// 사각형의 네 변을 모두 순회한 뒤에도 겹치는 도형이 발견되지 않았다면, false를 반환

	OutFill.x = 0;
	OutFill.y = 0;
	const int X0 = Origin.x;
	const int Y0 = Origin.y;
	const int X1 = Origin.x + Dimension.x - 1;
	const int Y1 = Origin.y + Dimension.y - 1;

	for (int X = X0; X <= X1; ++X)
	{
		if (MaskBitmap[Y0][X] == false && GetPixel(hdc, X, Y0) != keyColor)
		{
			OutFill.x = X;
			OutFill.y = Y0;
			return true;
		}
		if (MaskBitmap[Y1][X] == false && GetPixel(hdc, X, Y1) != keyColor)
		{
			OutFill.x = X;
			OutFill.y = Y1;
			return true;
		}
	}

	for (int Y = Y0; Y < Y1; ++Y)
	{
		if (MaskBitmap[Y][X1] == false && GetPixel(hdc, X1, Y) != keyColor)
		{
			OutFill.x = X0;
			OutFill.y = Y;
			return true;
		}
		if (MaskBitmap[Y][X1] == false && GetPixel(hdc, X1, Y) != keyColor)
		{
			OutFill.x = X1;
			OutFill.y = Y;
			return true;
		}
	}
	return false;
}

void Sprite::GetTightBounds(HDC hdc, std::vector<std::vector<bool>> MaskBitmap, COLORREF& keyColor, CD2DPointF& OutOrigin, CD2DPointF& OutDimension)
{
	OutOrigin.x = 0;
	OutOrigin.y = 0;
	OutDimension.x = MaskBitmap[0].size();
	OutDimension.y = MaskBitmap.size();


	// TightenBounds
	int Top = OutOrigin.y;
	int Bottom = OutOrigin.y + OutDimension.y - 1;
	int Left = OutOrigin.x;
	int Right = OutOrigin.x + OutDimension.x - 1;

	while (Top < Bottom && IsRowEmpty(hdc, keyColor, Left, Right, Top))
	{
		++Top;
	}
	while (Bottom >= Top && IsRowEmpty(hdc, keyColor, Left, Right, Bottom))
	{
		--Bottom;
	}
	while (Left < Right && IsColumnEmpty(hdc, keyColor, Left, Top, Bottom))
	{
		++Left;
	}
	while (Right >= Left && IsColumnEmpty(hdc, keyColor, Right, Top, Bottom))
	{
		--Right;
	}
	OutOrigin.x = Left;
	OutOrigin.y = Top;
	OutDimension.x = Right - Left + 1;
	OutDimension.y = Bottom - Top + 1;		// unreal 하고 좌표계가 달라서 확인 해봐야 할 듯
}

bool Sprite::IsRowEmpty(HDC hdc, COLORREF& keyColor, int X0, int X1, int Y)
{
	return IsRowEqual(hdc, keyColor, X0, X1, Y);
}

bool Sprite::IsRowEqual(HDC hdc, COLORREF& keyColor, int X0, int X1, int Y)
{
	for (int X = X0; X <= X1; ++X)
	{
		if (GetPixel(hdc, X, Y) != keyColor)
		{
			return false;
		}
	}
	return true;
}

bool Sprite::IsColumnEmpty(HDC hdc, COLORREF& keyColor, int X, int Y0, int Y1)
{
	return IsColumnEqual(hdc,keyColor,X,Y0,Y1);
}

bool Sprite::IsColumnEqual(HDC hdc, COLORREF& keyColor, int X, int Y0, int Y1)
{
	for (int Y = Y0; Y <= Y1; ++Y)
	{
		if (GetPixel(hdc, X, Y) != keyColor)
		{
			return false;
		}
	}
	return true;
}

void Sprite::FillRect(std::vector<std::vector<bool>>& MaskBitmap, int StartX, int StartY, int InWidth, int InHeight)
{
	const int X0 = StartX;
	const int Y0 = StartY;
	const int X1 = StartX + InWidth - 1;
	const int Y1 = StartY + InHeight - 1;
	for (int Y = Y0; Y <= Y1; ++Y)
	{
		for (int X = X0; X <= X1; ++X)
		{
			MaskBitmap[Y][X] = true;
		}
	}
}
