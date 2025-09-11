
// ResourceManagerToolDoc.h: CResourceManagerToolDoc 클래스의 인터페이스
//


#pragma once

class Scene;
class DataControl;
class CResourceManagerToolDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CResourceManagerToolDoc() noexcept;
	DECLARE_DYNCREATE(CResourceManagerToolDoc)

// 특성입니다.
public:
	// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CResourceManagerToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS



	// my Code
public:
	DataControl* GetDataControl() { return m_dataControl; }

	// 현재 선택된 씬의 정보 캡슐화
	Scene* GetCurrentScene() const { return m_currentScene; }
	void SetCurrentScene(Scene* val) { m_currentScene = val; }
	
	// 파일 리스트 컨트롤을 관리하는 뷰
	class FileManagerView* m_fileManagerView = nullptr;

	// 상대 경로 지정 폴더를 관리하는 뷰
	class FolderView* m_folderView = nullptr;
protected:
	DataControl* m_dataControl;

	Scene* m_currentScene = nullptr;
	// end my code
};
