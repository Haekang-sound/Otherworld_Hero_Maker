#pragma once



// FolderView 폼 보기

class FolderView : public CFormView
{
	DECLARE_DYNCREATE(FolderView)

protected:
	FolderView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~FolderView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FOLDER_VIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

public:
	// my Code
	void SelectFolder();
	void SetTextRelativePath();
	class CResourceManagerToolDoc* pDoc = nullptr;
private:
	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	// end my Code


	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedSetDirectoryBtn();
	CStatic m_path;
};


