#pragma once
#include <afx.h>
class Sprite : public CObject
{
public:
	Sprite();
	virtual ~Sprite();

	/*int m_lx = 0;	int m_ly = 0;
	int m_rx = 0;
	int m_ry = 0;*/

	
	int m_keyColor = 0;


	CD2DBitmap* m_d2dBitmap;


	void ExtractPixelData();


	/// <summary>
	///  내가 진짜 개 삽질한 것. 아무 의미 없음. Unreal 보고 따라했는데 뭔지 모르겠음..ㅋㅋ
	/// </summary>
	/// <param name="hdc"></param>
	/// <param name="sprite"></param>
	/// <param name="keyColor"></param>
	/// <param name="outRects"></param>
	static void ExtractRectsFromSprites(HDC hdc, Sprite* sprite, COLORREF& keyColor, std::vector<CD2DRectU>& outRects);
	static void ExtractRects(Sprite* sprite, std::vector<D2D1_RECT_F>& outRects);
private:
	static bool HasConnectedRect(HDC hdc, COLORREF& keyColor, const int X, const int Y, CD2DPointF& OutOrigin, CD2DPointF& OutDimension, int Width, int Height);
	static void FloodFill(HDC hdc, COLORREF& keyColor, std::vector<std::vector<bool>>& maskBitmap, int startX, int startY);
	static bool HasOverlappingIsland(HDC hdc, std::vector<std::vector<bool>> MaskBitmap, COLORREF& keyColor, const CD2DPointF& Origin, const CD2DPointF& Dimension, CD2DPointF& OutFill);
	static void GetTightBounds(HDC hdc, std::vector<std::vector<bool>> MaskBitmap, COLORREF& keyColor, CD2DPointF& OutOrigin, CD2DPointF& OutDimension);

	static bool IsRowEmpty(HDC hdc, COLORREF& keyColor, int X0, int X1, int Y);
	static bool IsRowEqual(HDC hdc, COLORREF& keyColor, int X0, int X1, int Y);

	static bool IsColumnEmpty(HDC hdc, COLORREF& keyColor, int X, int Y0, int Y1);
	static bool IsColumnEqual(HDC hdc, COLORREF& keyColor, int X, int Y0, int Y1);

	static void FillRect(std::vector<std::vector<bool>>& MaskBitmap, int StartX, int StartY, int InWidth, int InHeight);
private:
};

