// SpriteInfoView.cpp: 구현 파일
//

#include "pch.h"
#include "Gyunity.h"
#include "SpriteInfoView.h"
#include "GyunityDoc.h"
#include "ExtractedSprite.h"
#include "GyunityView.h"
// SpriteInfoView

IMPLEMENT_DYNCREATE(SpriteInfoView, CFormView)

SpriteInfoView::SpriteInfoView()
	: CFormView(IDD_SpriteInfo)
	, m_spriteCx(0)
	, m_spriteCy(0)
	, m_spriteName(_T(""))
	, m_spritePx(0)
	, m_spritePy(0)
	, m_spriteX(0)
	, m_spriteY(0)
{

}

SpriteInfoView::~SpriteInfoView()
{
}

void SpriteInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_CX, m_spriteCx);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_CY, m_spriteCy);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_NAME, m_spriteName);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_PX, m_spritePx);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_PY, m_spritePy);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_X, m_spriteX);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_Y, m_spriteY);

	((CGyunityDoc*)GetDocument())->m_spriteInfoView = this;
}

BEGIN_MESSAGE_MAP(SpriteInfoView, CFormView)
	ON_BN_CLICKED(IDC_SPRITE_APPLY, &SpriteInfoView::OnBnClickedSpriteApply)
END_MESSAGE_MAP()


// SpriteInfoView 진단

#ifdef _DEBUG
void SpriteInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SpriteInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}



#endif
#endif //_DEBUG


void SpriteInfoView::GetSpriteInfo(ExtractedSprite* extractedSprite)
{
	if (extractedSprite == nullptr) return;

	UpdateData(TRUE);

	m_currentExtractedSprite = extractedSprite;

	//CString cstr = _T("Hello, World!");
	//std::wstring wstr(CT2W(cstr));
	m_spriteName = _T("");
	m_spriteName.Append(extractedSprite->Name.c_str());
	m_spriteX = extractedSprite->Left;
	m_spriteY = extractedSprite->Top;
	m_spriteCx = extractedSprite->Right;
	m_spriteCy = extractedSprite->Bottom;
	m_spritePx = extractedSprite->PivotX;
	m_spritePy = extractedSprite->PivotY;

	UpdateData(FALSE);
}

// SpriteInfoView 메시지 처리기


void SpriteInfoView::OnBnClickedSpriteApply()
{
	if (m_currentExtractedSprite == nullptr) 
		return;
	UpdateData(TRUE);
	m_currentExtractedSprite->Name = CT2W(m_spriteName);
	m_currentExtractedSprite->Left = m_spriteX;
	m_currentExtractedSprite->Top = m_spriteY;
	m_currentExtractedSprite->Right = m_spriteCx;
	m_currentExtractedSprite->Bottom = m_spriteCy;
	m_currentExtractedSprite->PivotX = m_spritePx;
	m_currentExtractedSprite->PivotY = m_spritePy;
	UpdateData(FALSE);

	((CGyunityDoc*)GetDocument())->m_mainView->Invalidate(TRUE);
}
