
// GyunityView.h: CGyunityView 클래스의 인터페이스
//

#pragma once
#include "GyunityDoc.h"
// my code
enum class MouseSelectState
{
	None,
	DrawBox,
	SelectBox,
};


// end my code
class CGyunityView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGyunityView() noexcept;
	DECLARE_DYNCREATE(CGyunityView)

// 특성입니다.
public:
	CGyunityDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGyunityView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	// MY CODE
public:
	void MyInitialize();
	void LoadBitMapByFilePath(const LPCTSTR& filePath, HINSTANCE hInst = nullptr);
	/// <summary>
	/// 매개변수로 받아온 point와 박스들의 위치가 겹치는지를 확인
	/// </summary>
	/// <param name="point"></param>
	/// <returns></returns>
	ExtractedSprite* IsBoxPosition(CPoint point);
	void AutoSlice(const SlicePivotInfo& pivotInfo, float costumeX = 0.5f, float costumeY = 0.5f);
	void GridByCellSize(const SlicePivotInfo& pivotInfo, float x, float y, float costumeX = 0.5f, float costumeY = 0.5f);
	void GridByCellCount(const SlicePivotInfo& pivotInfo, int c, int r, float coustomX = 0.5f, float coustomY = 0.5f);
	void AutoSliceV2();

	CD2DPointF GetPivotByInfo(const SlicePivotInfo& pivotInfo, const CD2DRectF& rect, float costumeX = 1, float costumeY = 1);

private:
	// 아래는 AutoSlice할 때를 위한 함수 및 변수들
	void DFSForAutoSlice(int& x, int& y, COLORREF& color, HDC& hdc);
	void BFSForAutoSlice(int& x, int& y, COLORREF& color, HDC& hdc);
 	const int dx[4] = { 0,1,0,-1 };
 	const int dy[4] = { -1,0,1,0 };

	std::vector<std::vector<bool>> m_visitedPixel;
	float m_thisMaxLeft, m_thisMaxRight, m_thisMaxTop, m_thisMaxBottom;
	int m_width, m_height;

	// 상자를 자르고 이름을 붙일 때 필요한 인덱스와 함수
	std::wstring MakeSpriteName();
	int m_spriteNameIndex = 0;

	CD2DTextFormat* m_pTextFormat;
	CD2DSolidColorBrush* m_pBlackBrush;
	

	std::unordered_map<std::wstring, Sprite*> m_sprites;
	// 마우스 드래그 rect 위치, pivot 위치
	float m_rectX, m_rectY, m_rectCx, m_rectCy;
	float m_pivotOffsetX, m_pivotOffsetY;
	float m_rectMinInterval;	// 상자의 최소 간격

	// 마우스를 조금만 움직여도 상자가 움직이니 살짝 여유를 둘 변수
	float m_prevSelectedPosX, m_prevSelectedPosY;
	float m_curSelectedPosX, m_curSelectedPosY;
	float m_mouseSelectedPosMinInterval;	// 초기 값 10
	bool m_canMoveSmooth;	// 마우스가 일정 범위를 넘으면 상자를 원할하게 정교한 위치로 세부 조정할 수 있게 하는 변수

	// 현재 클릭된 상태인지 
	bool m_isClicked;
	// 마우스로 선택된 상자
	ExtractedSprite* m_selectedBox;
	// 현재 마우스가 해야할 일
	MouseSelectState m_mouseSelectState;

	// 다중 선택 함수 및 변수
	void PushSelectedBox(ExtractedSprite* box);
	void ClearSelectedBox();
	std::queue<ExtractedSprite*> m_selectedBoxQueue;
	int m_selectedCount = 0;
	bool m_shiftDown = false;


	// End My Code

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	// my code
	CD2DSolidColorBrush* m_pGreenBrush;
	// end my code
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNewImage();
	afx_msg void OnSize(UINT nType, int cx, int cy);
//protected:
public:
	afx_msg void OnAnimationPlay();
	afx_msg void OnAnimationReverseplay();
	afx_msg void OnAnimationStop();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // GyunityView.cpp의 디버그 버전
// inline CGyunityDoc* CGyunityView::GetDocument() const
//    { return reinterpret_cast<CGyunityDoc*>(m_pDocument); }
#endif