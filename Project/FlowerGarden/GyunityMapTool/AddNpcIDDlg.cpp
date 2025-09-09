// AddNpcIDDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GyunityMapTool.h"
#include "afxdialogex.h"
#include "AddNpcIDDlg.h"


// AddNpcIDDlg 대화 상자

IMPLEMENT_DYNAMIC(AddNpcIDDlg, CDialogEx)

AddNpcIDDlg::AddNpcIDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NPC_ID_DLG, pParent)
	, m_npcId(0)
{

}

AddNpcIDDlg::~AddNpcIDDlg()
{
}

void AddNpcIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_npcId);
}


BEGIN_MESSAGE_MAP(AddNpcIDDlg, CDialogEx)
END_MESSAGE_MAP()


// AddNpcIDDlg 메시지 처리기
