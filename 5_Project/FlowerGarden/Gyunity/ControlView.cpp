// ControlView.cpp: 구현 파일
//

#include "pch.h"
#include "Gyunity.h"
#include "ControlView.h"
#include "GyunityDoc.h"
#include "DataControl.h"
#include "GyunityView.h"
// ControlView

IMPLEMENT_DYNCREATE(ControlView, CFormView)

ControlView::ControlView()
	: CFormView(IDD_CONTROL_VIEW)
{

}

ControlView::~ControlView()
{
}

void ControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ControlView, CFormView)
	ON_BN_CLICKED(IDC_SAVE_SPRITE, &ControlView::OnBnClickedSaveSprite)
	ON_BN_CLICKED(IDC_LOAD_SPRITE, &ControlView::OnBnClickedLoadSprite)
END_MESSAGE_MAP()


// ControlView 진단

#ifdef _DEBUG
void ControlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ControlView 메시지 처리기


void ControlView::OnBnClickedSaveSprite()
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
			pDoc->m_dataControl->SaveSpriteData(tempfilename);	// 한 모션을 저장한다
		}
		//((CGyunityDoc*)GetDocument())->SaveSpriteData();
}


void ControlView::OnBnClickedLoadSprite()
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
		pDoc->m_dataControl->LoadSpriteData(tempfilename);	// 한 모션을 저장한다
	}
	((CGyunityDoc*)GetDocument())->m_mainView->Invalidate();

}
