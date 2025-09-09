// MapBrushView.cpp: 구현 파일
//

#include "pch.h"
#include "GyunityMapTool.h"
#include "MapBrushView.h"
#include "GyunityMapToolDoc.h"
#include "GyunityMapToolView.h"
#include "DataControl.h"
#include "NPCManagerView.h"

#include "MyMap.h"
#include "TileManager.h"
#include "Tile.h"
#include "Grid.h"
#include "TileBrush.h"
#include "ResourceManager.h"
// MapBrushView

IMPLEMENT_DYNCREATE(MapBrushView, CFormView)

MapBrushView::MapBrushView()
	: CFormView(IDD_MAP_BRUSH_VIEW)
{

}

MapBrushView::~MapBrushView()
{
}

void MapBrushView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	pDoc = (CGyunityMapToolDoc*)GetDocument();
	pDoc->m_mapBrushView = this;
	DDX_Control(pDX, IDC_TILE_LIST, m_tileList);

	//GetDocument()->GetDataControl()->SetRenderTarget(GetRenderTarget());
	//pDoc->GetDataControl()->SetRenderTarget(pDoc->m_mainView->GetRenderTarget());

}

BEGIN_MESSAGE_MAP(MapBrushView, CFormView)
	ON_BN_CLICKED(IDC_ADD_TILE_BTN, &MapBrushView::OnBnClickedAddTileBtn)
	ON_BN_CLICKED(IDC_DELETE_TILE_BTN, &MapBrushView::OnBnClickedDeleteTileBtn)
	ON_LBN_SELCHANGE(IDC_TILE_LIST, &MapBrushView::OnLbnSelchangeTileList)
	ON_BN_CLICKED(IDC_ADD_BASE_TILE_BTN, &MapBrushView::OnBnClickedAddBaseTileBtn)
	ON_BN_CLICKED(IDC_SAVE_TILE_BTN, &MapBrushView::OnBnClickedSaveTileBtn)
	ON_BN_CLICKED(IDC_LOAD_TILE_BTN, &MapBrushView::OnBnClickedLoadTileBtn)
	ON_BN_CLICKED(IDC_ERASE_BTN, &MapBrushView::OnBnClickedEraserBtn)
END_MESSAGE_MAP()


// MapBrushView 진단

#ifdef _DEBUG
void MapBrushView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MapBrushView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


#endif
#endif //_DEBUG


void MapBrushView::SetUnSelectWorldTile()
{
	m_tileList.SetCurSel(-1);
}

Tile* MapBrushView::MakeTile(CD2DBitmap* bitmap)
{
	Tile* tile = new Tile();
	tile->SetBitmap(bitmap);
	return tile;
}

void MapBrushView::AddTile()
{
	LPCTSTR ll = { _T("Image Files(*.bmp;*.png;*.jpg;*.jepg||") };
	CFileDialog dlg(TRUE, _T(".bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ll);
	if (dlg.DoModal() == IDOK)
	{
		CString tempFilePath;


		tempFilePath = dlg.GetPathName();
		// 파일 경로를 알았으니 파일을 불러와야 함.

		CD2DBitmap* bitmap = pDoc->m_mainView->LoadBitmapByFilePath(tempFilePath);
		// 여기서 사이즈 검사..? 잘 몰루

		// 타일을 만든다.
		Tile* tile = MakeTile(bitmap);

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
		m_tileList.InsertString(pDoc->GetDataControl()->GetTileManager()->GetTileCount(), name.c_str());

		// 타일매니저에 추가
		pDoc->GetDataControl()->GetTileManager()->AddTile(tile);

		// 그리드에 추가
		pDoc->m_mainView->m_mapGrid->AddTile(tile);
		pDoc->m_mainView->m_groundGrid->AddTile(tile);
	}
}

void MapBrushView::DeleteTile()
{
	MessageBox(_T("더미 파일이지롱"));
}


void MapBrushView::SaveTile()
{
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CString tempfilename;
		tempfilename = dlg.GetPathName();
		pDoc->GetDataControl()->SaveTile(tempfilename);
	}
}

void MapBrushView::LoadTile()
{
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(TRUE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		pDoc->m_mainView->m_groundGrid->ClearTiles();
		pDoc->m_mainView->m_mapGrid->ClearTiles();

		CString tempfilename;
		tempfilename = dlg.GetPathName();
		pDoc->GetDataControl()->LoadTile(tempfilename);

		RefreshTile();
	}
	//Invalidate();
	//UpdateData(TRUE);
	//UpdateData(FALSE);
}

void MapBrushView::RefreshTile()
{
	// 일단 리스트 초기화
	m_tileList.ResetContent();

	int tileCount = pDoc->GetDataControl()->GetTileManager()->GetTileCount();
	for (int i = 0; i < tileCount; i++)
	{
		// 타일에 데이터를 가져와 리스트에 추가
		Tile* tile = pDoc->GetDataControl()->GetTileManager()->GetTileByIndex(i);
		m_tileList.InsertString(i, tile->GetName().c_str());

		// 그리드에 타일을 넣긴 하는데 스읍.. 다른데서 해야할 것 같긴 한데 일단 여기서 함.
		pDoc->m_mainView->m_mapGrid->AddTile(tile);
		pDoc->m_mainView->m_groundGrid->AddTile(tile);
	}
}

// MapBrushView 메시지 처리기


void MapBrushView::OnBnClickedAddTileBtn()
{
	AddTile();
}


void MapBrushView::OnBnClickedDeleteTileBtn()
{
	DeleteTile();
}


void MapBrushView::OnLbnSelchangeTileList()
{
	int nCurSel = m_tileList.GetCurSel();
	if (nCurSel <= -1)
	{
		MessageBox(_T("선택된 타일이 없습니다."));
		return;
	}
	pDoc->m_mainView->SetTileType(TileType::World);
	pDoc->m_npcManagerView->SetUnSelectNpcTile();
	pDoc->m_mainView->SetCurrentTile(pDoc->GetDataControl()->GetTileManager()->GetTileByIndex(nCurSel));
	pDoc->m_mainView->SetTileIndex(nCurSel);
}


void MapBrushView::OnBnClickedAddBaseTileBtn()
{
	pDoc->m_mainView->m_mapGrid->Initialize(pDoc->m_mainView->GetTileBrush());

	std::wstring path = ResourceManager::GetInstance().GetImagePath(L"base.png");

	Tile* baseTile = new Tile();
	CD2DBitmap* baseTileBitmap = pDoc->m_mainView->LoadBitmapByFilePath(path.c_str());
	baseTile->SetBitmap(baseTileBitmap);
	pDoc->m_mainView->m_mapGrid->SetBaseTile(baseTile);
	pDoc->m_mainView->Invalidate();
}


void MapBrushView::OnBnClickedSaveTileBtn()
{
	SaveTile();
}


void MapBrushView::OnBnClickedLoadTileBtn()
{
	
	LoadTile();
}




void MapBrushView::OnBnClickedEraserBtn()
{
	// 타일을 선택한 것을 취소 함.
	m_tileList.SetCurSel(-1);

	if (pDoc->m_groundBaseTile == nullptr)
	{
		pDoc->m_mainView->m_groundGrid->Initialize(pDoc->m_mainView->GetTileBrush());

		std::wstring path = ResourceManager::GetInstance().GetImagePath(L"grid.png");
		Tile* baseTile = new Tile();
		CD2DBitmap* baseTileBitmap = pDoc->m_mainView->LoadBitmapByFilePath(path.c_str());
		baseTile->SetBitmap(baseTileBitmap);

		pDoc->m_mainView->m_groundGrid->SetBaseTile(baseTile);
		pDoc->m_groundBaseTile = baseTile;
	}

	pDoc->m_mainView->SetCurrentTile(pDoc->m_groundBaseTile);
	pDoc->m_mainView->SetTileIndex(-1);
}


void MapBrushView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//std::wstring path = L"../GyunityMapTool/resource/TileData.txt";
	//pDoc->GetDataControl()->LoadTile(path.c_str());
	//RefreshTile();
}
