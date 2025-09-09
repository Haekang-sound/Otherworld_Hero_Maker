// SpriteEditorView.cpp: 구현 파일
//

#include "pch.h"
#include "Gyunity.h"
#include "SpriteEditorView.h"
#include "AnimationView.h"

// SpriteEditorView

IMPLEMENT_DYNCREATE(SpriteEditorView, CFormView)

SpriteEditorView::SpriteEditorView()
	: CFormView(IDD_SPRITE_EDIT)
	, m_typeInfo(_T(""))
	, m_cellColumn(0)
	, m_cellRow(0)
	, m_cellSizeX(0)
	, m_cellSizeY(0)
	, m_pivotX(0)
	, m_pivotY(0)
{

}

SpriteEditorView::~SpriteEditorView()
{
}

void SpriteEditorView::LoadBitMapByFilePath(LPCTSTR filePath)
{
	HINSTANCE hResInstance = AfxGetResourceHandle();
	//if(hInst) AfxSetResourceHandle(hInst);

	CGyunityDoc* pDoc = (CGyunityDoc*)GetDocument();
	//ASSERT_VALID(pDoc);
	//pDoc->m_rt = m_pRenderTarget;
	m_pRenderTarget = pDoc->m_rt;
	Sprite* sprite = new Sprite();
	sprite->m_d2dBitmap = new CD2DBitmap(m_pRenderTarget, filePath, CD2DSizeU(0, 0), TRUE);
	sprite->m_d2dBitmap->Create(m_pRenderTarget);
	AfxSetResourceHandle(hResInstance);


	// 애니메이션 뷰용 비트맵을 또 만들어야 함.
	m_pRenderTarget = pDoc->m_rtAnimationView;
	Sprite* sprite2 = new Sprite();
	sprite2->m_d2dBitmap = new CD2DBitmap(m_pRenderTarget, filePath, CD2DSizeU(0, 0), TRUE);
	sprite2->m_d2dBitmap->Create(m_pRenderTarget);
	AfxSetResourceHandle(hResInstance);

	CD2DSizeF size = sprite->m_d2dBitmap->GetSize();
	CD2DRectF rectangle(0.0f, 0.0f, size.width, size.height);
	pDoc->m_dataControl->m_sprites.insert({ L"test", sprite });
	
	// document의 메인 스프라이트 초기화
	pDoc->m_dataControl->m_mainSprite = sprite;

	// doucment의 애니메이션 뷰 스프라이트 초기화
	pDoc->m_dataControl->m_animationViewSprite = sprite2;

	m_pRenderTarget = nullptr;
}

void SpriteEditorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_TYPE_COMBO, m_typeInfo);
	DDX_Text(pDX, IDC_Cell_Column, m_cellColumn);
	DDX_Text(pDX, IDC_Cell_Row, m_cellRow);
	DDX_Text(pDX, IDC_Cell_SizeX, m_cellSizeX);
	DDX_Text(pDX, IDC_Cell_SizeY, m_cellSizeY);
	DDX_Text(pDX, IDC_PX_EDIT, m_pivotX);
	DDX_Text(pDX, IDC_PY_EDIT, m_pivotY);
}

BEGIN_MESSAGE_MAP(SpriteEditorView, CFormView)
	ON_BN_CLICKED(IDC_LOADBMP_BTN, &SpriteEditorView::OnBnClickedLoadbmpBtn)
	ON_BN_CLICKED(IDC_SLICE_BTN, &SpriteEditorView::OnBnClickedSliceBtn)
END_MESSAGE_MAP()


// SpriteEditorView 진단

#ifdef _DEBUG
void SpriteEditorView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SpriteEditorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SpriteEditorView 메시지 처리기


void SpriteEditorView::OnBnClickedLoadbmpBtn()
{
	LPCTSTR ll = { _T("Image Files(*.bmp;*.png;*.jpg;*.jepg||") };
	CFileDialog dlg(TRUE, _T(".bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ll);
	if (dlg.DoModal() == IDOK)
	{
		GetDocument();
		CString tempFilePath;

		// 메인 스프라이트의 이름을 확장자 빼고 설정
		{
			std::wstring name = CT2W(dlg.GetFileName());

			int i = name.size() - 1;
			while (name[i] != '.')
			{
				name.pop_back();
				i--;
			}
			name.pop_back();

			((CGyunityDoc*)GetDocument())->m_dataControl->m_mainSpriteName = name;
		}

		tempFilePath = dlg.GetPathName();
		// 파일 경로를 알았으니 파일을 불러와야 함.
		LoadBitMapByFilePath(tempFilePath);

		// message를 보내 자동 새로고침을 함. 이게 맞는 구조인지는 잘 모르겠음.. 스파게티화 되는 중ㅋㅋ
		((CGyunityDoc*)GetDocument())->m_mainView->Invalidate(TRUE);
		((CGyunityDoc*)GetDocument())->m_animationView->Invalidate(TRUE);
	}
}


void SpriteEditorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// 대화 상자가 출력될 떄 초기화하는 곳.
	

	// 아래의 초기화는 ComboBox가 아무것도 선택되지 않는 것을 방지하기위해 초기화하는 코드
	((CComboBox*)GetDlgItem(IDC_TYPE_COMBO))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_PIVOT_COMBO))->SetCurSel(0);
}


void SpriteEditorView::OnBnClickedSliceBtn()
{
	// Slice Button

	CGyunityDoc* pDoc = (CGyunityDoc*)GetDocument();
	//ASSERT_VALID(pDoc);
	// UpdateData가 없어도 index는 잘 불러옴
	UpdateData(TRUE);

	SliceTypeInfo sliceTypeInfoIdx = (SliceTypeInfo)((CComboBox*)GetDlgItem(IDC_TYPE_COMBO))->GetCurSel();
	SlicePivotInfo slicePivotInfoIdx = (SlicePivotInfo)((CComboBox*)GetDlgItem(IDC_PIVOT_COMBO))->GetCurSel();
	switch (sliceTypeInfoIdx)
	{
	case Automatic:
	{
		pDoc->m_mainView->AutoSlice(slicePivotInfoIdx, m_pivotX, m_pivotY);
	}
		break;
	case GridByCellSize:
	{
		pDoc->m_mainView->GridByCellSize(slicePivotInfoIdx, m_cellSizeX, m_cellSizeY, m_pivotX, m_pivotY);
	}
		break;
	case GridByCellCount:
	{
		pDoc->m_mainView->GridByCellCount(slicePivotInfoIdx, m_cellColumn, m_cellRow, m_pivotX, m_pivotY);
	}
		break;
	case Test:
	{
		// 안씀.
		pDoc->m_mainView->AutoSliceV2();
	}
	break;
	default:
		break;
	}
	UpdateData(FALSE);
}
