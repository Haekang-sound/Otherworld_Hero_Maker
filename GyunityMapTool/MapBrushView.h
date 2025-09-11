#pragma once



// MapBrushView 폼 보기
class CGyunityMapToolDoc;
class Tile;
class MapBrushView : public CFormView
{
	DECLARE_DYNCREATE(MapBrushView)

protected:
	MapBrushView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~MapBrushView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAP_BRUSH_VIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	// my code
public:
	void SetUnSelectWorldTile();
	Tile* MakeTile(CD2DBitmap* bitmap);
	void AddTile();
	void DeleteTile();

	void SaveTile();
	void LoadTile();

	/// <summary>
	/// 현재 리스트에 있는 타일들을 갱신한다.
	/// </summary>
	void RefreshTile();
private:
	CGyunityMapToolDoc* pDoc = nullptr;
	

	// end my code

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddTileBtn();
	afx_msg void OnBnClickedDeleteTileBtn();
	afx_msg void OnLbnSelchangeTileList();
	CListBox m_tileList;
	afx_msg void OnBnClickedAddBaseTileBtn();
	afx_msg void OnBnClickedSaveTileBtn();
	afx_msg void OnBnClickedLoadTileBtn();
	afx_msg void OnBnClickedEraserBtn();
	virtual void OnInitialUpdate();
};


