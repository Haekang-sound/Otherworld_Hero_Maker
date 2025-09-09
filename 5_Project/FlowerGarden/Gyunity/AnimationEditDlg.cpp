// AnimationEditDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Gyunity.h"
#include "afxdialogex.h"
#include "AnimationEditDlg.h"


// AnimationEditDlg 대화 상자

IMPLEMENT_DYNAMIC(AnimationEditDlg, CDialogEx)

AnimationEditDlg::AnimationEditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANIMATION_EDIT_DLG, pParent)
	, m_animationName(_T(""))
	, m_delayTime(0)
{

}

AnimationEditDlg::~AnimationEditDlg()
{
}


void AnimationEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANIMATION_NAME, m_animationName);
	DDX_Text(pDX, IDC_DELAY_TIME, m_delayTime);
}

void AnimationEditDlg::SetAnimation()
{
	
}


BEGIN_MESSAGE_MAP(AnimationEditDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AnimationEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AnimationEditDlg 메시지 처리기


void AnimationEditDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
