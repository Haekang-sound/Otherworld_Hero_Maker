// MapManagerView.cpp: 구현 파일
//

#include "pch.h"
#include "GyunityMapTool.h"
#include "MapManagerView.h"

#include "GyunityMapToolDoc.h"
#include "GyunityMapToolView.h"
#include "DataControl.h"

#include "MyMap.h"
#include "AddMapDlg.h"

#include "Global.h"
#include "ResourceManager.h"
#include "Tile.h"
#include "Grid.h"

// MapManagerView

IMPLEMENT_DYNCREATE(MapManagerView, CFormView)

MapManagerView::MapManagerView()
	: CFormView(IDD_MAP_MANAGER_VIEW)
	, m_groundCheck(FALSE)
	, m_mapCheck(FALSE)
	, m_Grid(FALSE)
{
}

MapManagerView::~MapManagerView()
{
}

void MapManagerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAP_LIST, m_mapList);

	pDoc = (CGyunityMapToolDoc*)GetDocument();
	pDoc->m_mapManagerView = this;
	DDX_Control(pDX, IDC_GROUND_LIST, m_groundList);
	DDX_Check(pDX, IDC_GROUND_CHECK, m_groundCheck);
	DDX_Check(pDX, IDC_MAP_CHECK, m_mapCheck);

	DDX_Control(pDX, IDC_GROUND_CHECK, m_groundCheckButton);
	DDX_Control(pDX, IDC_MAP_CHECK, m_mapCheckButton);


	// 	m_mapCheckButton.SetCheck(TRUE);
	DDX_Check(pDX, IDC_Grid, m_Grid);
	DDX_Control(pDX, IDC_Grid, m_gridCheckButton);
}

void MapManagerView::AddGround()
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
		m_groundList.InsertString(pDoc->GetDataControl()->GetGroundCount(), dlg.m_mapName);

		// 새로운 맵 데이터
		MyMap* newMap = new MyMap();

		newMap->CreateMap(dlg.m_x, dlg.m_x);
		newMap->SetName(std::wstring(CT2W(dlg.m_mapName)));

		pDoc->GetDataControl()->AddGround(newMap);
		UpdateData(FALSE);
	}
}

void MapManagerView::DeleteGround()
{
	int nCurSel = m_groundList.GetCurSel();

	if (nCurSel == -1)
	{
		MessageBox(_T("선택된 바닥이 없습니다."));
		return;
	}

	if (nCurSel >= 0)
	{
		// 리스트에서 삭제
		m_groundList.DeleteString(nCurSel);


		// 실제 데이터 삭제
		pDoc->GetDataControl()->DeleteGroundByIndex(nCurSel);
		pDoc->SetCurrentGround(nullptr);
		pDoc->m_mainView->m_groundGrid->SetCurrentWorld(nullptr);
		pDoc->m_mainView->Invalidate();
	}
}

void MapManagerView::AddMap()
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
		m_mapList.InsertString(pDoc->GetDataControl()->GetMapCount(), dlg.m_mapName);

		// 새로운 맵 데이터
		MyMap* newMap = new MyMap();
		
		newMap->CreateMap(dlg.m_x,dlg.m_x);
		newMap->SetName(std::wstring(CT2W(dlg.m_mapName)));

		pDoc->GetDataControl()->AddMap(newMap);

		UpdateData(FALSE);
	}
}

void MapManagerView::DeleteMap()
{
	int nCurSel = m_mapList.GetCurSel();

	if (nCurSel == -1)
	{
		MessageBox(_T("선택된 맵이 없습니다."));
		return;
	}

	if (nCurSel >= 0)
	{
		// 리스트에서 삭제
		m_mapList.DeleteString(nCurSel);
		

		// 실제 데이터 삭제
		pDoc->GetDataControl()->DeleteMapByIndex(nCurSel);
		pDoc->SetCurrentMap(nullptr);
		pDoc->m_mainView->m_mapGrid->SetCurrentWorld(nullptr);
		pDoc->m_mainView->Invalidate();
	}
}

void MapManagerView::SaveMap()
{
	int nCurSel = m_mapList.GetCurSel();
	if (nCurSel == -1)
	{
		MessageBox(_T("선택된 맵이 없습니다."));
		return;
	}
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CString tempfilename;
		tempfilename = dlg.GetPathName();
		pDoc->GetDataControl()->SaveMap(tempfilename, nCurSel);
	}
}

void MapManagerView::SaveMapAll()
{
	CFolderPickerDialog folderPicker;
	if (folderPicker.DoModal() == IDOK)
	{
		CString folderPath = folderPicker.GetFolderPath();

		pDoc->GetDataControl()->SaveMapAll(folderPath);
	}
}

void MapManagerView::LoadMapOne()
{
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(TRUE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CString tempfilename;
		tempfilename = dlg.GetPathName();
		pDoc->GetDataControl()->LoadMap(tempfilename);


		MyMap* map = pDoc->GetDataControl()->GetMapByIndex(pDoc->GetDataControl()->GetMapCount() - 1);

		m_mapList.InsertString(pDoc->GetDataControl()->GetMapCount() - 1, map->GetName().c_str());
	}
}

void MapManagerView::SaveGround()
{
	int nCurSel = m_groundList.GetCurSel();
	if (nCurSel == -1)
	{
		MessageBox(_T("선택된 바닥이 없습니다."));
		return;
	}
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CString tempfilename;
		tempfilename = dlg.GetPathName();
		pDoc->GetDataControl()->SaveGround(tempfilename, nCurSel);
	}
}

void MapManagerView::SaveGroundAll()
{
	CFolderPickerDialog folderPicker;
	if (folderPicker.DoModal() == IDOK)
	{
		CString folderPath = folderPicker.GetFolderPath();

		pDoc->GetDataControl()->SaveGroundAll(folderPath);
	}
}

void MapManagerView::LoadGroundOne()
{
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(TRUE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CString tempfilename;
		tempfilename = dlg.GetPathName();
		pDoc->GetDataControl()->LoadGround(tempfilename);


		MyMap* map = pDoc->GetDataControl()->GetGroundByIndex(pDoc->GetDataControl()->GetGroundCount() - 1);

		m_groundList.InsertString(pDoc->GetDataControl()->GetGroundCount() - 1, map->GetName().c_str());
	}
}

BEGIN_MESSAGE_MAP(MapManagerView, CFormView)
	ON_LBN_SELCHANGE(IDC_MAP_LIST, &MapManagerView::OnLbnSelchangeMapList)
	ON_BN_CLICKED(IDC_ADD_MAP_BTN, &MapManagerView::OnBnClickedAddMapBtn)
	ON_BN_CLICKED(IDC_DELETE_MAP_BTN, &MapManagerView::OnBnClickedDeleteMapBtn)
	ON_BN_CLICKED(IDC_SAVE_MAP_BTN, &MapManagerView::OnBnClickedSaveMapBtn)
	ON_LBN_SELCHANGE(IDC_GROUND_LIST, &MapManagerView::OnLbnSelchangeGroundList)
	ON_BN_CLICKED(IDC_ADD_GROUND_BTN, &MapManagerView::OnBnClickedAddGroundBtn)
	ON_BN_CLICKED(IDC_DELETE_GROUND_BTN, &MapManagerView::OnBnClickedDeleteGroundBtn)
	ON_BN_CLICKED(IDC_SIZE_RESET_BTN, &MapManagerView::OnBnClickedSizeResetBtn)
	ON_BN_CLICKED(IDC_SAVEALL_MAP_BTN, &MapManagerView::OnBnClickedSaveallMapBtn)
	ON_BN_CLICKED(IDC_SAVE_DATA_BTN, &MapManagerView::OnBnClickedSaveDataBtn)
	ON_BN_CLICKED(IDC_LOAD_DATA_BTN, &MapManagerView::OnBnClickedLoadDataBtn)
	ON_BN_CLICKED(IDC_SAVEALL_GROUND_BTN, &MapManagerView::OnBnClickedSaveallGroundBtn)
	ON_BN_CLICKED(IDC_SAVE_GROUND_BTN, &MapManagerView::OnBnClickedSaveGroundBtn)
	ON_BN_CLICKED(IDC_LOAD_GROUND_BTN, &MapManagerView::OnBnClickedLoadGroundBtn)
	ON_BN_CLICKED(IDC_LOAD_MAP_BTN, &MapManagerView::OnBnClickedLoadMapBtn)
	ON_BN_CLICKED(IDC_GROUND_CHECK, &MapManagerView::OnBnClickedGroundCheck)
	ON_BN_CLICKED(IDC_MAP_CHECK, &MapManagerView::OnBnClickedMapCheck)
	ON_BN_CLICKED(IDC_Grid, &MapManagerView::OnBnClickedGrid)
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// MapManagerView 진단

#ifdef _DEBUG
void MapManagerView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MapManagerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MapManagerView 메시지 처리기


void MapManagerView::OnLbnSelchangeMapList()
{
	int nCurSel = m_mapList.GetCurSel();
	if (nCurSel == -1)
	{
		pDoc->SetCurrentMap(nullptr);
		return;
	}

	m_groundList.SetCurSel(-1);

	pDoc->m_mainView->SetGridType(GridType::Map);
	// 기본 타일 설정. 만약 없을 경우 새로 만듦.
	if (pDoc->m_baseTile == nullptr)
	{
		pDoc->m_mainView->m_mapGrid->Initialize(pDoc->m_mainView->GetTileBrush());

		std::wstring path = ResourceManager::GetInstance().GetImagePath(L"grid.png");

		Tile* baseTile = new Tile();
		CD2DBitmap* baseTileBitmap = pDoc->m_mainView->LoadBitmapByFilePath(path.c_str());
		baseTile->SetBitmap(baseTileBitmap);
		pDoc->m_mainView->m_mapGrid->SetBaseTile(baseTile);
		pDoc->m_baseTile = baseTile;
	}

	// 현재 맵 변경
	MyMap* curMap = pDoc->GetDataControl()->GetMapByIndex(nCurSel);
	pDoc->SetCurrentMap(curMap);
	pDoc->m_mainView->Invalidate();
	//pDoc->m_mainView->m_grid->SetCurrentWorld(curMap->GetWorldData());
}


void MapManagerView::OnBnClickedAddMapBtn()
{
	// AddMap
	AddMap();
}


void MapManagerView::OnBnClickedDeleteMapBtn()
{
	// DeleteMap
	DeleteMap();
}


void MapManagerView::OnBnClickedSaveMapBtn()
{
	SaveMap();
}


void MapManagerView::OnLbnSelchangeGroundList()
{
	int nCurSel = m_groundList.GetCurSel();
	if (nCurSel == -1)
	{
		pDoc->SetCurrentGround(nullptr);
		return;
	}
	// 맵 리스트를 선택 해제
	m_mapList.SetCurSel(-1);

	pDoc->m_mainView->SetGridType(GridType::Ground);
	// 기본 타일 설정. 만약 없을 경우 새로 만듦.
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

	// 현재 맵 변경
	MyMap* curMap = pDoc->GetDataControl()->GetGroundByIndex(nCurSel);
	pDoc->SetCurrentGround(curMap);
	pDoc->m_mainView->Invalidate();
}


void MapManagerView::OnBnClickedAddGroundBtn()
{
	AddGround();
}


void MapManagerView::OnBnClickedDeleteGroundBtn()
{
	DeleteGround();
}


void MapManagerView::OnBnClickedSizeResetBtn()
{
	// 사이즈 초기화
	g_Scale = 1.f;
	pDoc->m_mainView->Invalidate();
}





void MapManagerView::OnBnClickedSaveallMapBtn()
{
	SaveMapAll();
}


void MapManagerView::OnBnClickedSaveDataBtn()
{
}


void MapManagerView::OnBnClickedLoadDataBtn()
{
}


void MapManagerView::OnBnClickedSaveallGroundBtn()
{
	SaveGroundAll();
}


void MapManagerView::OnBnClickedSaveGroundBtn()
{
	// ground save
	SaveGround();
}


void MapManagerView::OnBnClickedLoadGroundBtn()
{
	// Load ground
	LoadGroundOne();
}


void MapManagerView::OnBnClickedLoadMapBtn()
{
	// Load Map
	LoadMapOne();
}


void MapManagerView::OnBnClickedGroundCheck()
{
 	UpdateData(TRUE);
 	pDoc->m_mainView->SetOnGround(m_groundCheck);
 	pDoc->m_mainView->Invalidate(TRUE);
 	UpdateData(FALSE);
}


void MapManagerView::OnBnClickedMapCheck()
{
	UpdateData(TRUE);
	pDoc->m_mainView->SetOnMap(m_mapCheck);
	pDoc->m_mainView->Invalidate(TRUE);
	UpdateData(FALSE);
}


void MapManagerView::OnBnClickedGrid()
{
	UpdateData(TRUE);
	pDoc->m_mainView->m_groundGrid->SetGridOn(m_Grid);
	pDoc->m_mainView->m_mapGrid->SetGridOn(m_Grid);
	pDoc->m_mainView->Invalidate();
	UpdateData(FALSE);
}


//int MapManagerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CFormView::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
//	m_groundCheckButton.SetCheck(TRUE);
//	m_mapCheckButton.SetCheck(TRUE);
//	return 0;
//}


void MapManagerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_groundCheckButton.SetCheck(TRUE);
	m_mapCheckButton.SetCheck(TRUE);
	m_gridCheckButton.SetCheck(TRUE);
}
