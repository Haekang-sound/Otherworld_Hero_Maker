// AddMapDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GyunityMapTool.h"
#include "afxdialogex.h"
#include "AddMapDlg.h"

// AddMapDlg 대화 상자

IMPLEMENT_DYNAMIC(AddMapDlg, CDialogEx)

AddMapDlg::AddMapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_MAP_DLG, pParent)
	, m_mapName(_T(""))
	, m_x(0)
{

}

AddMapDlg::~AddMapDlg()
{
}

void AddMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MAP_NAME, m_mapName);

	DDX_Text(pDX, IDC_COL_EDIT, m_x);
	//  DDX_Text(pDX, IDC_ROW_EDIT, m_Row);
}


BEGIN_MESSAGE_MAP(AddMapDlg, CDialogEx)
END_MESSAGE_MAP()


// AddMapDlg 메시지 처리기
