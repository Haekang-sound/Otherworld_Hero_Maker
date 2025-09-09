#pragma once



// NPCManagerView 폼 보기
class CGyunityMapToolDoc;
class Tile;
class NPCManagerView : public CFormView
{
	DECLARE_DYNCREATE(NPCManagerView)

protected:
	NPCManagerView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~NPCManagerView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NPC_MANAGER_VIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()



	// my code
public:
	void SetUnSelectNpcTile();
private:
	void AddNpcLayer();
	CGyunityMapToolDoc* pDoc = nullptr;

	Tile* MakeTile(CD2DBitmap* bitmap);

	// end my code
public:
	// NPC를 그릴 그리드의 리스트
	CListBox m_npcLayerList;
	afx_msg void OnBnClickedNpcAddBtn();
	afx_msg void OnBnClickedNpcDeleteBtn();
	afx_msg void OnBnClickedNpcLayerSaveBtn();

	CListBox m_npcTileList;
	afx_msg void OnBnClickedNpcTileAddBtn();
	afx_msg void OnBnClickedNpcTileDeleteBtn();
	afx_msg void OnBnClickedNpcTileSaveBtn();
	afx_msg void OnLbnSelchangeNpcTileList();
	afx_msg void OnLbnSelchangeNpcLayer();
	CButton m_npcLayerCheckButton;
	BOOL m_npcLayerCheck;
	afx_msg void OnBnClickedNpcLayerBtn();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedNpcUndoBtn();
};


