// FileManagerView.cpp: 구현 파일
//

#include "pch.h"
#include "ResourceManagerTool.h"
#include "ResourceManagerToolDoc.h"
#include "FileManagerView.h"
#include "Scene.h"
#include "MyFile.h"

// FileManagerView

IMPLEMENT_DYNCREATE(FileManagerView, CFormView)

FileManagerView::FileManagerView()
	: CFormView(IDD_FILES_VIEW)
{

}

FileManagerView::~FileManagerView()
{
	delete m_defaultBitmap;
}

void FileManagerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_fileList);

	pDoc = (CResourceManagerToolDoc*)GetDocument();
	pDoc->m_fileManagerView = this;

	//m_imageList.Create(30, 30, ILC_COLORDDB, 1, 0);
	m_imageList.Create(30, 30, ILC_COLORDDB, 1, 0);

	m_fileList.SetImageList(&m_imageList, LVSIL_NORMAL);
	m_fileList.SetExtendedStyle(m_fileList.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT |	// 아이템이 선택되면 모든 서브 아이템이 하이라이트 된다.
		LVS_EX_GRIDLINES |		// 아이템과 서브아이템 주위에 그리드가 생긴다.
		LVS_EX_HEADERDRAGDROP	// 드래그 앤 드롭을 가능하게 한다.
	);

	m_fileList.InsertColumn(0, _T("파일"), LVCFMT_LEFT, 150);

	m_defaultBitmap = new CBitmap();
	m_defaultBitmap->LoadBitmapW(IDB_DEFAULT_ICON);
	//m_fileList.SetColumnWidth(0, 300);

	
	//m_fileList.SetExtendedStyle()
}

BEGIN_MESSAGE_MAP(FileManagerView, CFormView)
	ON_WM_DROPFILES()
	ON_WM_MEASUREITEM()
	ON_WM_MEASUREITEM()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &FileManagerView::OnLvnItemchangedList1)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// FileManagerView 진단

#ifdef _DEBUG
void FileManagerView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void FileManagerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void FileManagerView::SetFileListControlByScene(Scene* scene)
{
	//int a = m_fileList.GetItemCount();
	m_fileList.DeleteAllItems();


	for (int i = 0; i < scene->GetFileCount(); i++)
	{
		MyFile* file = scene->GetFileByIndex(i);

		int nItem;

		CString fileName;
		fileName.Append(file->GetName().c_str());
		nItem = m_fileList.InsertItem(i, fileName);
	}

}

void FileManagerView::Clear()
{
	m_fileList.DeleteAllItems();
}

void FileManagerView::SetAlign(bool isTop)
{
	DWORD dwStyle = m_fileList.GetStyle();


// 	dwStyle &= ~LVS_REPORT;
// 	dwStyle |= LVS_ALIGNTOP;
// 
// 	m_fileList.ModifyStyle(LVS_REPORT | LVS_ALIGNLEFT, dwStyle);
// 
// 	return;

	if (isTop)
	{
		//dwStyle &= ~WS_BORDER;
		dwStyle &= ~LVS_REPORT;
		dwStyle |= LVS_ALIGNTOP;
		m_fileList.ModifyStyle(LVS_REPORT | LVS_ALIGNLEFT, LVS_ALIGNTOP, dwStyle);

	}
	else
	{
		dwStyle &= ~LVS_ALIGNTOP;
		dwStyle |= LVS_REPORT;
		m_fileList.ModifyStyle(LVS_ALIGNTOP,LVS_REPORT | LVS_ALIGNLEFT, dwStyle);
	}

	//m_fileList.ModifyStyle(0, dwStyle);
	Invalidate();
}

// FileManagerView 메시지 처리기


void FileManagerView::OnDropFiles(HDROP hDropInfo)
{
	if (pDoc->GetCurrentScene() == nullptr)
	{
		MessageBox(_T("선택된 씬이 없습니다."));
		return;
	}

	TCHAR fullFilePath[_MAX_PATH];
	int TotalFiles = ::DragQueryFile(hDropInfo, 0xFFFFFFFF, fullFilePath, _MAX_PATH);

	// 이제 갯수를 알 수 있다.
	for (int i = 0; i < TotalFiles; i++)
	{
		// 드롭된 갯수만큼 실행한다.
		::DragQueryFile(hDropInfo, i, fullFilePath, _MAX_PATH);
		// 테스트용
		//AfxMessageBox(fullFilePath);

		// 아래는 파일의 경로가 아닌 이름만 추출
		CString fileName = CFile(fullFilePath, CFile::modeRead).GetFileName();//CFile::GetFileName();

		int nItem;
		// test
		//int a = pDoc->GetCurrentScene()->GetFileCount();
		nItem = m_fileList.InsertItem(pDoc->GetCurrentScene()->GetFileCount(), fileName);

		// 실제 데이터 저장
		MyFile* newFile = new MyFile();
		newFile->SetName(std::wstring(CT2W(fileName)));
		newFile->SetPath(fullFilePath);
		pDoc->GetCurrentScene()->AddFile(newFile);
	}
	

	// 끝.
	::DragFinish(hDropInfo);

	CFormView::OnDropFiles(hDropInfo);
}




void FileManagerView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMeasureItemStruct->itemHeight += 250;      //  - 연산 설정하면 높이가 줄어듭니다.
	lpMeasureItemStruct->itemWidth += 250;      //  - 연산 설정하면 높이가 줄어듭니다.
	CFormView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void FileManagerView::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	POSITION pos = m_fileList.GetFirstSelectedItemPosition();

	int beforeIdx = m_itemIndex;
	m_itemIndex = m_fileList.GetNextItem(-1, LVNI_SELECTED);

	if (m_itemIndex == -1)
	{
		m_itemIndex = beforeIdx;
		return;
	}
	//CString result


	/// Test
// 	CString temp;
// 	temp.Format(_T("%d"), m_itemIndex);
// 
// 	MessageBox(temp);



	*pResult = 0;
}


void FileManagerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//if (nChar == VK_DELETE)
	//{
	//	if (pDoc->GetCurrentScene() == nullptr)
	//	{
	//		return;
	//	}

	//	if (m_itemIndex >= 0)
	//	{
	//		m_fileList.DeleteItem(m_itemIndex);
	//		pDoc->GetCurrentScene()->DeleteFileByIndex(m_itemIndex);
	//		//m_itemIndex = -1;
	//	}
	//}

	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL FileManagerView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_DELETE)
		{
			if (pDoc->GetCurrentScene() == nullptr)
			{
				return CFormView::PreTranslateMessage(pMsg);
			}

			if (m_itemIndex >= 0)
			{
				pDoc->GetCurrentScene()->DeleteFileByIndex(m_itemIndex);
				SetFileListControlByScene(pDoc->GetCurrentScene());
// 				m_fileList.DeleteItem(m_itemIndex);
// 
// 				m_fileList.DeleteItem(m_fileList.GetItemCount() - 1);
// 				for (int i = m_itemIndex; i < m_fileList.GetItemCount(); i++)
// 				{
// 					//CString strIdex
// 					m_fileList.InsertItem(i - 1, pDoc->GetCurrentScene()->GetFileByIndex(i)->GetName().c_str());
// 				}
// 				//m_fileList.SortItems();
				m_itemIndex = -1;
			}
		}
	}
	return CFormView::PreTranslateMessage(pMsg);
}
