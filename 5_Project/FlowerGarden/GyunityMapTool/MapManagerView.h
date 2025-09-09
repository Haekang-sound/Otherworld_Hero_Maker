#pragma once



// MapManagerView 폼 보기
class CGyunityMapToolDoc;
class MapManagerView : public CFormView
{
	DECLARE_DYNCREATE(MapManagerView)

protected:
	MapManagerView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~MapManagerView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAP_MANAGER_VIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// my code
public:
private:
	CGyunityMapToolDoc* pDoc = nullptr;

	void AddGround();
	void DeleteGround();

	void AddMap();
	void DeleteMap();

	void SaveMap();
	void SaveMapAll();
	void LoadMapOne();

	void SaveGround();
	void SaveGroundAll();
	void LoadGroundOne();
	// end my code

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeMapList();

	// 맵 리스트입니다.
	CListBox m_mapList;
	afx_msg void OnBnClickedAddMapBtn();
	afx_msg void OnBnClickedDeleteMapBtn();
	afx_msg void OnBnClickedSaveMapBtn();
	afx_msg void OnLbnSelchangeGroundList();
	CListBox m_groundList;
	afx_msg void OnBnClickedAddGroundBtn();
	afx_msg void OnBnClickedDeleteGroundBtn();
	afx_msg void OnBnClickedSizeResetBtn();
	afx_msg void OnBnClickedSaveallMapBtn();
	afx_msg void OnBnClickedSaveDataBtn();
	afx_msg void OnBnClickedLoadDataBtn();
	afx_msg void OnBnClickedSaveallGroundBtn();
	afx_msg void OnBnClickedSaveGroundBtn();
	afx_msg void OnBnClickedLoadGroundBtn();
	afx_msg void OnBnClickedLoadMapBtn();
	BOOL m_groundCheck;
	BOOL m_mapCheck;
	afx_msg void OnBnClickedGroundCheck();
	CButton m_groundCheckButton;
	CButton m_mapCheckButton;
	afx_msg void OnBnClickedMapCheck();
	BOOL m_Grid;
	CButton m_gridCheckButton;
	afx_msg void OnBnClickedGrid();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
};


