// AddSceneDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ResourceManagerTool.h"
#include "afxdialogex.h"
#include "AddSceneDlg.h"


// AddSceneDlg 대화 상자

IMPLEMENT_DYNAMIC(AddSceneDlg, CDialogEx)

AddSceneDlg::AddSceneDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_SCENE_DLG, pParent)
	, m_newSceneName(_T(""))
{

}

AddSceneDlg::~AddSceneDlg()
{
}

void AddSceneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCENE_NAME, m_newSceneName);
}


BEGIN_MESSAGE_MAP(AddSceneDlg, CDialogEx)
END_MESSAGE_MAP()


// AddSceneDlg 메시지 처리기
