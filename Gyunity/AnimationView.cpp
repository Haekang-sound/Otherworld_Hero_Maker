// AnimationView.cpp: 구현 파일
//

#include "pch.h"
#include "Gyunity.h"
#include "AnimationView.h"
#include "SpriteAnimation.h"
#include "ExtractedSprite.h"
#include "Sprite.h"
#include "GyunityDoc.h"
// AnimationView

IMPLEMENT_DYNCREATE(AnimationView, CFormView)

AnimationView::AnimationView()
	: CFormView(IDD_AnimationView)
{
	EnableD2DSupport();

	m_pBlackBrush = new CD2DSolidColorBrush(
		GetRenderTarget(),
		D2D1::ColorF(D2D1::ColorF::Black)
	);
}

AnimationView::~AnimationView()
{
}

void AnimationView::SetDelayTime(int t)
{
	 delayTime = t; 
	 SetTimer(1, delayTime, NULL);
}

void AnimationView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	((CGyunityDoc*)GetDocument())->m_animationView = this;
	((CGyunityDoc*)GetDocument())->m_rtAnimationView = m_pRenderTarget;
}

BEGIN_MESSAGE_MAP(AnimationView, CFormView)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// AnimationView 진단

#ifdef _DEBUG
void AnimationView::AssertValid() const
{
	CFormView::AssertValid();

}

#ifndef _WIN32_WCE
void AnimationView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// AnimationView 메시지 처리기


void AnimationView::OnDraw(CDC* /*pDC*/)
{
	CGyunityDoc* pDoc = (CGyunityDoc*)GetDocument();
	//ASSERT_VALID(pDoc);

	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Gray));
	

	if (m_renderAnimation != nullptr)
	{
		m_maxFrame = m_renderAnimation->m_sprites.size();
		// temp 1 before m_maxFrame
		//for (int frame = 0; frame < 1; frame++)
		{
			ExtractedSprite* spr = m_renderAnimation->m_sprites[m_frame];
 			CD2DBitmap* bitmap = pDoc->m_dataControl->m_animationViewSprite->m_d2dBitmap;
 			CD2DSizeF size = bitmap->GetSize();
 			CD2DRectF rectangle(0, 0, size.width, size.height);
 			CD2DRectF rectangle2(spr->Left, spr->Top, spr->Right, spr->Bottom);
 			m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(-spr->Left, -spr->Top));
 			//m_pRenderTarget->DrawBitmap(bitmap, &rectangle);
			m_pRenderTarget->DrawBitmap(bitmap, &rectangle2, 1.0,D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &rectangle2);
			m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		}
	}

	m_pRenderTarget->EndDraw();
}

void AnimationView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		m_frame++;
		if (m_frame >= m_maxFrame)
		{
			// TODO : 0이 되는 경우가 있는데 확인해야 함.
			m_frame %= m_maxFrame;
		}
		Invalidate();
	}

	CFormView::OnTimer(nIDEvent);
}


void AnimationView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	SetTimer(1, delayTime, NULL);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
