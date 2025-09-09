#pragma once
#include "afxdialogex.h"


// AddMapDlg 대화 상자

class CGyunityMapToolDoc;
class AddMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddMapDlg)

public:
	AddMapDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AddMapDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_MAP_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


	// my code
public:
private:

	// end my code

	DECLARE_MESSAGE_MAP()
public:
	CString m_mapName;
	int m_x;
//	int m_y;
};
