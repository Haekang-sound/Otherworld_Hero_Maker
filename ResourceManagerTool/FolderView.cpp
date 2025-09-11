// FolderView.cpp: 구현 파일
//

#include "pch.h"
#include "ResourceManagerTool.h"
#include "FolderView.h"
#include "ResourceManagerToolDoc.h"
#include "DataControl.h"

#include "Global.h"

// FolderView

IMPLEMENT_DYNCREATE(FolderView, CFormView)

FolderView::FolderView()
	: CFormView(IDD_FOLDER_VIEW)
{

}

FolderView::~FolderView()
{
}

void FolderView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//SelectFolder();
	pDoc = (CResourceManagerToolDoc*)GetDocument();
	pDoc->m_folderView = this;
	DDX_Control(pDX, IDC_STATIC_PATH, m_path);
}

void FolderView::SelectFolder()
{
	ITEMIDLIST* pidlBrowse;
	WCHAR       pszPathname[MAX_PATH];

	BROWSEINFO  BrInfo;
	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;

	memset(&BrInfo, 0x00, sizeof(BrInfo));
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = _T("Select folder");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	// 이벤트에 대한 사용자정의 함수
	BrInfo.lpfn = BrowseCallbackProc;

	// 사용자정의 함수에 넘겨질 인자로 사용자가 설정하고자 하는 경로를 설정한다.
	// 예를들어 초기폴더경로를 C드라이브로 설정하는 경우
	CString strInitPath = _T("C:\\");
	BrInfo.lParam = (LPARAM)strInitPath.GetBuffer();

	pidlBrowse = ::SHBrowseForFolder(&BrInfo);
	if (pidlBrowse != NULL)
	{
		// 선택된 폴더 경로얻음
		SHGetPathFromIDList(pidlBrowse, pszPathname);

		// 경로(pszPathname)를 이용하여 이후작업 추가
	}
}

void FolderView::SetTextRelativePath()
{
	m_path.SetWindowTextW(g_relativePath.c_str());

}

int CALLBACK FolderView::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg) {
		// 폴더선택 다이얼로그의 초기화가 끝난 경우
	case BFFM_INITIALIZED:
		//SendMessage((UINT)hwnd, BFFM_SETSELECTION, TRUE, lpData);
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		break;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(FolderView, CFormView)
	ON_BN_CLICKED(IDC_SET_DIRECTORY_BTN, &FolderView::OnBnClickedSetDirectoryBtn)
END_MESSAGE_MAP()


// FolderView 진단

#ifdef _DEBUG
void FolderView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void FolderView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// FolderView 메시지 처리기


void FolderView::OnBnClickedSetDirectoryBtn()
{
	// 상대 경로 지정
	CFolderPickerDialog dlg(NULL, OFN_FILEMUSTEXIST, NULL, 0);

	if (dlg.DoModal() == IDOK)
	{
		CString relativePathName = dlg.GetFileName();

		pDoc->GetDataControl()->SetRelativePath(std::wstring(CT2W(relativePathName)));
		//extern std::wstring g_relativePath;
		g_relativePath = std::wstring(CT2W(relativePathName));

		m_path.SetWindowTextW(relativePathName);

		// 모든 씬과 파일의 상대 경로 수정
		pDoc->GetDataControl()->SetScenesRelativePath();
	}
}
