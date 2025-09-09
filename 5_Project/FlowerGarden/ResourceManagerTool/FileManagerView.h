#pragma once



// FileManagerView 폼 보기

class FileManagerView : public CFormView
{
	DECLARE_DYNCREATE(FileManagerView)

protected:
	FileManagerView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~FileManagerView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILES_VIEW };
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
	CResourceManagerToolDoc* pDoc;

	CBitmap* m_defaultBitmap;
	/// <summary>
	/// 지정된 씬의 파일들을 현재 리스트 컨트롤에 보이게합니다.
	/// </summary>
	/// <param name="scene"></param>
	void SetFileListControlByScene(Scene* scene);

	void Clear();


	/// <summary>
	/// 맞춤 방식을 변경 
	/// </summary>
	/// <param name="isTop"></param>
	void SetAlign(bool isTop);
private:

	// 현재 선택한 아이템의 인덱스
	int m_itemIndex;
	

	// end my code
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);

	CImageList m_imageList;
	// 파일 리스트 입니당
	CListCtrl m_fileList;
	
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


