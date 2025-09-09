#pragma once
#include "afxdialogex.h"


// AddNpcIDDlg 대화 상자

class AddNpcIDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddNpcIDDlg)

public:
	AddNpcIDDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AddNpcIDDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NPC_ID_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_npcId;
};
