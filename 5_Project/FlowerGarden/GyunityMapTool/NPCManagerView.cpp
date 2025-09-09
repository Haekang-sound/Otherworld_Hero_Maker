// NPCManagerView.cpp: 구현 파일
//

#include "pch.h"
#include "GyunityMapTool.h"
#include "NPCManagerView.h"
#include "GyunityMapToolDoc.h"
#include "AddMapDlg.h"
#include "DataControl.h"
#include "MyMap.h"
#include "GyunityMapToolView.h"
#include "Grid.h"
#include "Tile.h"
#include "NPCTileManager.h"
#include "MapManagerView.h"
#include "ResourceManager.h"
#include "MapBrushView.h"
#include "NPCGrid.h"
#include "AddNpcIDDlg.h"
// NPCManagerView

IMPLEMENT_DYNCREATE(NPCManagerView, CFormView)

NPCManagerView::NPCManagerView()
	: CFormView(IDD_NPC_MANAGER_VIEW)
	, m_npcLayerCheck(FALSE)
{

}

NPCManagerView::~NPCManagerView()
{
}

void NPCManagerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NPC_LAYER, m_npcLayerList);

	pDoc = (CGyunityMapToolDoc*)GetDocument();
	pDoc->m_npcManagerView = this;
	DDX_Control(pDX, IDC_NPC_TILE_LIST, m_npcTileList);
	DDX_Control(pDX, IDC_NPC_LAYER_BTN, m_npcLayerCheckButton);
	DDX_Check(pDX, IDC_NPC_LAYER_BTN, m_npcLayerCheck);
}

void NPCManagerView::SetUnSelectNpcTile()
{
	m_npcTileList.SetCurSel(-1);
}

void NPCManagerView::AddNpcLayer()
{
	AddMapDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);

		if (dlg.m_x == 0)
		{
			MessageBox(_T("사이즈가 0보다 커야합니다."));
			return;
		}
		// 새로운 맵 정보 리스트에 추가
		m_npcLayerList.InsertString(pDoc->GetDataControl()->GetNPCLayerCount(), dlg.m_mapName);

		// 새로운 맵 데이터
		MyMap* newMap = new MyMap();

		newMap->CreateMap(dlg.m_x, dlg.m_x, true);
		newMap->SetName(std::wstring(CT2W(dlg.m_mapName)));

		pDoc->GetDataControl()->AddNPCLayer(newMap);
		UpdateData(FALSE);
	}
}

Tile* NPCManagerView::MakeTile(CD2DBitmap* bitmap)
{
	Tile* tile = new Tile();
	tile->SetBitmap(bitmap);
	return tile;
}

BEGIN_MESSAGE_MAP(NPCManagerView, CFormView)
	ON_BN_CLICKED(IDC_NPC_ADD_BTN, &NPCManagerView::OnBnClickedNpcAddBtn)
	ON_BN_CLICKED(IDC_NPC_DELETE_BTN, &NPCManagerView::OnBnClickedNpcDeleteBtn)
	ON_BN_CLICKED(IDC_NPC_LAYER_SAVE_BTN, &NPCManagerView::OnBnClickedNpcLayerSaveBtn)
	ON_BN_CLICKED(IDC_NPC_TILE_ADD_BTN, &NPCManagerView::OnBnClickedNpcTileAddBtn)
	ON_BN_CLICKED(IDC_NPC_TILE_DELETE_BTN, &NPCManagerView::OnBnClickedNpcTileDeleteBtn)
	ON_BN_CLICKED(IDC_NPC_TILE_SAVE_BTN, &NPCManagerView::OnBnClickedNpcTileSaveBtn)
	ON_LBN_SELCHANGE(IDC_NPC_TILE_LIST, &NPCManagerView::OnLbnSelchangeNpcTileList)
	ON_LBN_SELCHANGE(IDC_NPC_LAYER, &NPCManagerView::OnLbnSelchangeNpcLayer)
	ON_BN_CLICKED(IDC_NPC_LAYER_BTN, &NPCManagerView::OnBnClickedNpcLayerBtn)
	ON_BN_CLICKED(IDC_NPC_UNDO_BTN, &NPCManagerView::OnBnClickedNpcUndoBtn)
END_MESSAGE_MAP()


// NPCManagerView 진단

#ifdef _DEBUG
void NPCManagerView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void NPCManagerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// NPCManagerView 메시지 처리기


void NPCManagerView::OnBnClickedNpcAddBtn()
{
	AddNpcLayer();
}


void NPCManagerView::OnBnClickedNpcDeleteBtn()
{
	int nCurSel = m_npcLayerList.GetCurSel();

	if (nCurSel == -1)
	{
		MessageBox(_T("선택된 NPC레이어가 없습니다."));
		return;
	}

	if (nCurSel >= 0)
	{
		// 리스트에서 삭제
		m_npcLayerList.DeleteString(nCurSel);

		// 실제 데이터 삭제
		pDoc->GetDataControl()->DeleteNPCLayerByIndex(nCurSel);
		pDoc->SetCurrentNPCLayer(nullptr);
		pDoc->m_mainView->m_npcGrid->SetCurrentWorld(nullptr);
		pDoc->m_mainView->Invalidate();
	}
}


void NPCManagerView::OnBnClickedNpcLayerSaveBtn()
{
	int nCurSel = m_npcLayerList.GetCurSel();
	if (nCurSel == -1)
	{
		MessageBox(_T("선택된 NPC레이어가 없습니다."));
		return;
	}
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CString tempfilename;
		tempfilename = dlg.GetPathName();
		pDoc->GetDataControl()->SaveNPCLayer(tempfilename, nCurSel);
	}
}


void NPCManagerView::OnBnClickedNpcTileAddBtn()
{
	LPCTSTR ll = { _T("Image Files(*.bmp;*.png;*.jpg;*.jepg||") };
	CFileDialog dlg(TRUE, _T(".bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ll);
	if (dlg.DoModal() == IDOK)
	{
		AddNpcIDDlg npcIdDlg;
		if (npcIdDlg.DoModal() == IDOK)
		{
			CString tempFilePath;


			tempFilePath = dlg.GetPathName();
			// 파일 경로를 알았으니 파일을 불러와야 함.

			CD2DBitmap* bitmap = pDoc->m_mainView->LoadBitmapByFilePath(tempFilePath);
			// 여기서 사이즈 검사..? 잘 몰루

			// 타일을 만든다.
			Tile* tile = MakeTile(bitmap);

			// 타일에 npc 정보 입력
			tile->SetNpcID(npcIdDlg.m_npcId);

			// 타일의 이름을 확장자 빼고 설정
			std::wstring name = CT2W(dlg.GetFileName());

			int i = name.size() - 1;
			while (name[i] != '.')
			{
				name.pop_back();
				i--;
			}
			name.pop_back();
			tile->SetName(name);
			// 타일의 경로 추가
			tile->SetFilePath(tempFilePath);

			// 뷰 리스트에 추가
			m_npcTileList.InsertString(pDoc->GetDataControl()->GetNPCTileManager()->GetTileCount(), name.c_str());

			// 타일매니저에 추가
			pDoc->GetDataControl()->GetNPCTileManager()->AddTile(tile);

			// 그리드에 추가
			pDoc->m_mainView->m_npcGrid->AddTile(tile);
			// 		pDoc->m_mainView->m_mapGrid->AddTile(tile);
			// 		pDoc->m_mainView->m_groundGrid->AddTile(tile);
		}
	}
}


void NPCManagerView::OnBnClickedNpcTileDeleteBtn()
{
}


void NPCManagerView::OnBnClickedNpcTileSaveBtn()
{	
}


void NPCManagerView::OnLbnSelchangeNpcTileList()
{
	int nCurSel = m_npcTileList.GetCurSel();
	if (nCurSel <= -1)
	{
		MessageBox(_T("선택된 타일이 없습니다."));
		return;
	}
	pDoc->m_mainView->SetTileType(TileType::NPC);
	pDoc->m_mapBrushView->SetUnSelectWorldTile();
	pDoc->m_mainView->SetCurrentTile(pDoc->GetDataControl()->GetNPCTileManager()->GetTileByIndex(nCurSel));
	pDoc->m_mainView->SetTileIndex(nCurSel);
}


void NPCManagerView::OnLbnSelchangeNpcLayer()
{
	int nCurSel = m_npcLayerList.GetCurSel();
	if (nCurSel == -1)
	{
		pDoc->SetCurrentNPCLayer(nullptr);
		return;
	}
	pDoc->m_mapManagerView->m_groundList.SetCurSel(-1);
	pDoc->m_mapManagerView->m_mapList.SetCurSel(-1);

	pDoc->m_mainView->SetGridType(GridType::NPC);
	// 기본 타일 설정. 만약 없을 경우 새로 만듦.
	if (pDoc->m_npcBaseTile == nullptr)
	{
		pDoc->m_mainView->m_npcGrid->Initialize(pDoc->m_mainView->GetTileBrush());

		std::wstring path = ResourceManager::GetInstance().GetImagePath(L"grid.png");

		Tile* baseTile = new Tile();
		CD2DBitmap* baseTileBitmap = pDoc->m_mainView->LoadBitmapByFilePath(path.c_str());
		baseTile->SetBitmap(baseTileBitmap);
		pDoc->m_mainView->m_npcGrid->SetBaseTile(baseTile);
		pDoc->m_npcBaseTile = baseTile;
	}

	// 현재 맵 변경
	MyMap* curMap = pDoc->GetDataControl()->GetNPCLayerByIndex(nCurSel);
	pDoc->SetCurrentNPCLayer(curMap);
	pDoc->m_mainView->Invalidate();

}


void NPCManagerView::OnBnClickedNpcLayerBtn()
{
	UpdateData(TRUE);
	pDoc->m_mainView->SetOnNPCLayer(m_npcLayerCheck);
	pDoc->m_mainView->Invalidate(TRUE);
	UpdateData(FALSE);
}


void NPCManagerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_npcLayerCheckButton.SetCheck(TRUE);
}


void NPCManagerView::OnBnClickedNpcUndoBtn()
{
	pDoc->m_mainView->m_npcGrid->UnDo();
	pDoc->m_mainView->Invalidate();
}
