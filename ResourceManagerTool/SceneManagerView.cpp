// SceneManagerView.cpp: 구현 파일
//

#include "pch.h"
#include "ResourceManagerTool.h"
#include "SceneManagerView.h"
#include "ResourceManagerToolDoc.h"
#include "AddSceneDlg.h"
#include "Scene.h"
#include "FileManagerView.h"
#include "DataControl.h"
#include "FolderView.h"
// SceneManagerView

IMPLEMENT_DYNCREATE(SceneManagerView, CFormView)

SceneManagerView::SceneManagerView()
	: CFormView(IDD_SCENE_VIEW)
	, m_alignTop(FALSE)
{

}

SceneManagerView::~SceneManagerView()
{
}

void SceneManagerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCENE_LIST, m_sceneList);
	pDoc = (CResourceManagerToolDoc*)GetDocument();
	DDX_Check(pDX, IDC_ALIGN_TOP, m_alignTop);
}

BEGIN_MESSAGE_MAP(SceneManagerView, CFormView)
	ON_LBN_SELCHANGE(IDC_SCENE_LIST, &SceneManagerView::OnLbnSelchangeSceneList)
	ON_BN_CLICKED(IDC_ADD_SCENE_BTN, &SceneManagerView::OnBnClickedAddSceneBtn)
	ON_BN_CLICKED(IDC_DELETE_SCENE_BTN, &SceneManagerView::OnBnClickedDeleteSceneBtn)
	ON_BN_CLICKED(IDC_SAVE_SCENE_BTN, &SceneManagerView::OnBnClickedSaveSceneBtn)
	ON_BN_CLICKED(IDC_SAVE_ALL_SCENE_BTN, &SceneManagerView::OnBnClickedSaveAllSceneBtn)
	ON_BN_CLICKED(IDC_SAVE_DATA_BTN, &SceneManagerView::OnBnClickedSaveDataBtn)
	ON_BN_CLICKED(IDC_LOAD_DATA_BTN, &SceneManagerView::OnBnClickedLoadDataBtn)
	ON_BN_CLICKED(IDC_ALIGN_TOP, &SceneManagerView::OnBnClickedAlignTop)
END_MESSAGE_MAP()


// SceneManagerView 진단

#ifdef _DEBUG
void SceneManagerView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SceneManagerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void SceneManagerView::AddScene()
{
	AddSceneDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);

		Scene* newScene = new Scene();
		std::wstring newName = CT2W(dlg.m_newSceneName);

		// 이름 설정
		newScene->SetSceneName(newName);

		UpdateData(FALSE);

		// view에 SceneList에 추가한 후 scene 카운트 증가
		m_sceneList.InsertString(m_sceneCount, dlg.m_newSceneName);
		m_sceneCount++;
		pDoc->GetDataControl()->AddSceneData(newScene);
	}
}

void SceneManagerView::DeleteScene()
{
	int nCurSel = m_sceneList.GetCurSel();

	if (nCurSel == -1)
	{
		MessageBox(_T("선택된 씬이 없습니다."));
		return;
	}

	if (nCurSel >= 0)
	{
		// 리스트에서 삭제
		m_sceneList.DeleteString(nCurSel);
		m_sceneCount--;

		// 실제 데이터 삭제
		pDoc->GetDataControl()->DeleteSceneDataByIndex(nCurSel);
		pDoc->SetCurrentScene(nullptr);
	}
}

// SceneManagerView 메시지 처리기


void SceneManagerView::OnLbnSelchangeSceneList()
{
	int nCurSel = m_sceneList.GetCurSel();
	if (nCurSel == -1)
	{
		pDoc->SetCurrentScene(nullptr);
		return;
	}
	// 현재 씬 변경
	Scene* curScene = pDoc->GetDataControl()->GetSceneByIndex(nCurSel);
	pDoc->SetCurrentScene(curScene);
	// TODO : 리스트 컨트롤 수정
	pDoc->m_fileManagerView->SetFileListControlByScene(curScene);
}


void SceneManagerView::OnBnClickedAddSceneBtn()
{
	// 새로운 씬을 만듭니다.
	AddScene();
}


void SceneManagerView::OnBnClickedDeleteSceneBtn()
{
	// 선택된 씬을 지웁니다.
	pDoc->GetCurrentScene()->Clear();
	DeleteScene();
}


void SceneManagerView::OnBnClickedSaveSceneBtn()
{
	if (pDoc->GetCurrentScene() == nullptr)
	{
		MessageBox(_T("선택된 씬이 없습니다."));
		return;
	}

	CFolderPickerDialog folderPicker;
	if (folderPicker.DoModal() == IDOK)
	{
		CString folderPath = folderPicker.GetFolderPath();

		pDoc->GetDataControl()->SaveSceneDataForGameEngine(folderPath, pDoc->GetCurrentScene());
	}
}


void SceneManagerView::OnBnClickedSaveAllSceneBtn()
{
	CFolderPickerDialog folderPicker;
	if (folderPicker.DoModal() == IDOK)
	{
		CString folderPath = folderPicker.GetFolderPath();

		pDoc->GetDataControl()->SaveAllSceneDataForGameEngine(folderPath);
	}
}


void SceneManagerView::OnBnClickedSaveDataBtn()
{
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		pDoc->GetDataControl()->SaveDataForTool(dlg.GetPathName());
	}
}


void SceneManagerView::OnBnClickedLoadDataBtn()
{


	// 다시 불러옴
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(TRUE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		// 일단 클리어
		m_sceneCount = 0;
		pDoc->GetDataControl()->Clear();
		pDoc->m_fileManagerView->Clear();
		m_sceneList.ResetContent();

		pDoc->GetDataControl()->LoadDataForTool(dlg.GetPathName());

		int sceneCount = pDoc->GetDataControl()->GetSceneSize();

		for (int i = 0; i < sceneCount; i++)
		{
			CString sceneName;
			sceneName.Append(pDoc->GetDataControl()->GetSceneByIndex(i)->GetSceneName().c_str());
			m_sceneList.InsertString(m_sceneCount, sceneName);
			m_sceneCount++;

			pDoc->m_folderView->SetTextRelativePath();
		}
	}
}


void SceneManagerView::OnBnClickedAlignTop()
{
	UpdateData(TRUE);
	
	pDoc->m_fileManagerView->SetAlign(m_alignTop);

	UpdateData(FALSE);
}
