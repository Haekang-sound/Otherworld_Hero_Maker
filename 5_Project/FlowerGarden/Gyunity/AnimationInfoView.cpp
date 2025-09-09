// AnimationInfoView.cpp: 구현 파일
//

#include "pch.h"
#include "Gyunity.h"
#include "AnimationInfoView.h"
#include "SpriteAnimation.h"
#include "GyunityDoc.h"
#include "GyunityView.h"
#include "AnimationAddDlg.h"
#include "AnimationEditDlg.h"
#include "AnimationView.h"

// AnimationInfoView

IMPLEMENT_DYNCREATE(AnimationInfoView, CFormView)

AnimationInfoView::AnimationInfoView()
	: CFormView(IDD_FORMVIEW)
{

}

AnimationInfoView::~AnimationInfoView()
{
}

void AnimationInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANIMATION_LIST, m_animationList);
}

BEGIN_MESSAGE_MAP(AnimationInfoView, CFormView)
	ON_BN_CLICKED(IDC_ADD_ANIMATION, &AnimationInfoView::OnBnClickedAddAnimation)
	ON_BN_CLICKED(IDC_DELETE_ANIMATION, &AnimationInfoView::OnBnClickedDeleteAnimation)
	ON_BN_CLICKED(IDC_SAVE_ANIMATION, &AnimationInfoView::OnBnClickedSaveAnimation)
	ON_BN_CLICKED(IDC_LOAD_ANIMATION, &AnimationInfoView::OnBnClickedLoadAnimation)
	ON_LBN_SELCHANGE(IDC_ANIMATION_LIST, &AnimationInfoView::OnLbnSelchangeAnimationList)
	ON_BN_CLICKED(IDC_EDIT_ANIMATION, &AnimationInfoView::OnBnClickedEditAnimation)
	ON_BN_CLICKED(IDC_SAVE_ANIMATION_ONE, &AnimationInfoView::OnBnClickedSaveAnimationOne)
END_MESSAGE_MAP()


// AnimationInfoView 진단

#ifdef _DEBUG
void AnimationInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void AnimationInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


#endif
#endif //_DEBUG

bool AnimationInfoView::AddAnimation()
{
	if (((CGyunityDoc*)GetDocument())->m_dataControl->m_selectedBoxQueue.empty())
	{
		return false;
	}

	AnimationAddDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);

		m_currentAnimName = CT2W(dlg.m_animationName);
		m_currentAnimDelayTime = dlg.m_delayTime;
		UpdateData(FALSE);
	}
	else
	{
		return false;
	}

	SpriteAnimation* newAnimation = new SpriteAnimation();
	newAnimation->m_name = m_currentAnimName;
	newAnimation->m_delayTime = m_currentAnimDelayTime;

	while (!((CGyunityDoc*)GetDocument())->m_dataControl->m_selectedBoxQueue.empty())
	{
		ExtractedSprite* exSpr = ((CGyunityDoc*)GetDocument())->m_dataControl->m_selectedBoxQueue.front();
		newAnimation->m_sprites.push_back(exSpr);
		exSpr->Selected = false;
		((CGyunityDoc*)GetDocument())->m_dataControl->m_selectedBoxQueue.pop();

	}

	((CGyunityDoc*)GetDocument())->m_dataControl->m_animations.push_back(newAnimation);
	return true;
}


void AnimationInfoView::LoadAnimation()
{
	for (int i = 0; i < m_animationCount; i++)
	{
		m_animationList.DeleteString(0);
	}

	m_animationCount = 0;
	for (int i = 0; i < ((CGyunityDoc*)GetDocument())->m_dataControl->m_animations.size(); i++)
	{
		m_animationList.InsertString(m_animationCount, ((CGyunityDoc*)GetDocument())->m_dataControl->m_animations[m_animationCount]->m_name.c_str());
		m_animationCount++;
	}
}

bool AnimationInfoView::EditAnimation()
{

	// 현재 ListBox에서 선택된 아이템의 인덱스를 받아오기
	// (만약 선택되어 있지 않다면 -1)
	int nCurSel = m_animationList.GetCurSel();

	if (nCurSel == -1)
	{
		MessageBox(_T("선택된 애니메이션이 없습니다."));
		return false;
	}

	AnimationEditDlg dlg;
	CString cstr;
	cstr.Append(((CGyunityDoc*)GetDocument())->m_dataControl->m_animations[nCurSel]->m_name.c_str());
	dlg.m_animationName = cstr;
	dlg.m_delayTime = ((CGyunityDoc*)GetDocument())->m_dataControl->m_animations[nCurSel]->m_delayTime;
	if (dlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);

		m_currentAnimName = CT2W(dlg.m_animationName);
		m_currentAnimDelayTime = dlg.m_delayTime;
		SpriteAnimation* curAnim = ((CGyunityDoc*)GetDocument())->m_dataControl->m_animations[nCurSel];

		curAnim->m_name = m_currentAnimName;
		curAnim->m_delayTime = m_currentAnimDelayTime;
		m_animationList.DeleteString(nCurSel);
		m_animationList.InsertString(nCurSel, m_currentAnimName.c_str());

		((CGyunityDoc*)GetDocument())->m_animationView->SetDelayTime(m_currentAnimDelayTime);
		UpdateData(FALSE);
	}
	else
	{
		return false;
	}

	return true;
}

int AnimationInfoView::GetAnimationIndex()
{
	int nCurSel = m_animationList.GetCurSel();

	if (nCurSel == -1)
	{
		MessageBox(_T("선택된 애니메이션이 없습니다."));
		return -1;
	}
	return nCurSel;
}

// AnimationInfoView 메시지 처리기


void AnimationInfoView::OnBnClickedAddAnimation()
{
	if (!AddAnimation())
	{
		MessageBox(_T("선택된 스프라이트가 없습니다."));
		return;
	}
	
	m_animationList.InsertString(m_animationCount, m_currentAnimName.c_str());
	m_animationCount++;
}


void AnimationInfoView::OnBnClickedDeleteAnimation()
{
	// 현재 ListBox에서 선택된 아이템의 인덱스를 받아오기
	// (만약 선택되어 있지 않다면 -1)
	int nCurSel = m_animationList.GetCurSel();

	if (nCurSel == -1)
	{
		MessageBox(_T("선택된 애니메이션이 없습니다."));
		return;
	}

	// 현재 선택된 아이템이 있다면
	if (nCurSel >= 0)
	{
		// 해당 아이템을 제거
		m_animationList.DeleteString(nCurSel);
	}
	// 아래 코드가 확실한지는 잘 모르겠다.
	((CGyunityDoc*)GetDocument())->m_dataControl->m_animations.erase(
		find(((CGyunityDoc*)GetDocument())->m_dataControl->m_animations.begin(),
			((CGyunityDoc*)GetDocument())->m_dataControl->m_animations.end(),
			((CGyunityDoc*)GetDocument())->m_dataControl->m_animations[nCurSel]
		)
	);
	m_animationCount--;
}


void AnimationInfoView::OnBnClickedSaveAnimation()
{
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CGyunityDoc* pDoc = (CGyunityDoc*)GetDocument();
		CString tempfilename;
		//tempfilename = dlg.GetFileName();
		tempfilename = dlg.GetPathName();
		pDoc->m_dataControl->SaveAnimationData(tempfilename);	
	}
}


void AnimationInfoView::OnBnClickedLoadAnimation()
{
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(TRUE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CGyunityDoc* pDoc = (CGyunityDoc*)GetDocument();
		CString tempfilename;
		//tempfilename = dlg.GetFileName();
		tempfilename = dlg.GetPathName();
		pDoc->m_dataControl->LoadAnimationData(tempfilename);
		LoadAnimation();
		pDoc->m_animationView->m_renderAnimation = nullptr;
	}
}


void AnimationInfoView::OnLbnSelchangeAnimationList()
{
	CGyunityDoc* pDoc = (CGyunityDoc*)GetDocument();

	int nCurSel = m_animationList.GetCurSel();

	if (nCurSel == -1)
	{
		return;
	}

	// TODO : 아래 코드 실행하면 오류 남. 아직은 사용하지 않지만 수정할 것.
// 	if (pDoc->m_dataControl->m_animationViewSprite->m_d2dBitmap == nullptr)
// 	{
// 		MessageBox(_T("메인 스프라이트가 없습니다."));
// 		return;
// 	}

	pDoc->m_animationView->m_renderAnimation = pDoc->m_dataControl->m_animations[nCurSel];
	pDoc->m_animationView->SetDelayTime(pDoc->m_dataControl->m_animations[nCurSel]->m_delayTime);
	pDoc->m_animationView->m_frame = 0;
	pDoc->m_animationView->Invalidate();
}


void AnimationInfoView::OnBnClickedEditAnimation()
{
	EditAnimation();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationInfoView::OnBnClickedSaveAnimationOne()
{
	int idx = GetAnimationIndex();

	if (idx == -1)
		return;

	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CGyunityDoc* pDoc = (CGyunityDoc*)GetDocument();
		CString tempfilename;
		tempfilename = dlg.GetPathName();
		pDoc->m_dataControl->SaveAnimationOneData(tempfilename,idx);
	}
	return;
}
