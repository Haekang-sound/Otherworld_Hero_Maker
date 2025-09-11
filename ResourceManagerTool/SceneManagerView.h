#pragma once



// SceneManagerView 폼 보기

class SceneManagerView : public CFormView
{
	DECLARE_DYNCREATE(SceneManagerView)

protected:
	SceneManagerView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~SceneManagerView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCENE_VIEW };
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
	class CResourceManagerToolDoc* pDoc = nullptr;
public:
	/// <summary>
	/// 새로운 씬을 추가합니다.
	/// </summary>
	void AddScene();

	/// <summary>
	/// 선택한 씬을 삭제합니다.
	/// </summary>
	void DeleteScene();

	// 씬의 카운트
	int m_sceneCount = 0;

	// end my code


	DECLARE_MESSAGE_MAP()
		afx_msg void OnLbnSelchangeSceneList();

	// 씬의 리스트를 관리합니다.
	CListBox m_sceneList;
	afx_msg void OnBnClickedAddSceneBtn();
	afx_msg void OnBnClickedDeleteSceneBtn();
	afx_msg void OnBnClickedSaveSceneBtn();
	afx_msg void OnBnClickedSaveAllSceneBtn();
	afx_msg void OnBnClickedSaveDataBtn();
	afx_msg void OnBnClickedLoadDataBtn();
	// 위로 맞춤 // false일때는 왼쪽 맞춤
	BOOL m_alignTop;
	afx_msg void OnBnClickedAlignTop();
};


