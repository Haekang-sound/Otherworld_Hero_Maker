// AnimationAddDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Gyunity.h"
#include "afxdialogex.h"
#include "AnimationAddDlg.h"


// AnimationAddDlg 대화 상자

IMPLEMENT_DYNAMIC(AnimationAddDlg, CDialogEx)

AnimationAddDlg::AnimationAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANIMATION_ADD_DLG, pParent)
	, m_animationName(_T(""))
	, m_delayTime(0)
{

}

AnimationAddDlg::~AnimationAddDlg()
{
}

void AnimationAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANIMATION_NAME, m_animationName);
	DDX_Text(pDX, IDC_DELAY_TIME, m_delayTime);
}


BEGIN_MESSAGE_MAP(AnimationAddDlg, CDialogEx)
END_MESSAGE_MAP()


// AnimationAddDlg 메시지 처리기
