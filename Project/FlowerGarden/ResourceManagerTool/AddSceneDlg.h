#pragma once
#include "afxdialogex.h"


// AddSceneDlg 대화 상자

class AddSceneDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddSceneDlg)

public:
	AddSceneDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AddSceneDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_ADD_SCENE_DLG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 새로 만들 씬의 이름입니다.
	CString m_newSceneName;
};
