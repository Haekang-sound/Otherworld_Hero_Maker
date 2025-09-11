
// GyunityMapToolDoc.h: CGyunityMapToolDoc 클래스의 인터페이스
//


#pragma once

class Tile;
class MyMap;
class DataControl;
class CGyunityMapToolView;
class MapManagerView;
class MapBrushView;
class NPCManagerView;
class CGyunityMapToolDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CGyunityMapToolDoc() noexcept;
	DECLARE_DYNCREATE(CGyunityMapToolDoc)

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
	virtual ~CGyunityMapToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// my code
public:
	DataControl* GetDataControl() { return m_dataControl; }

	void SetCurrentMap(MyMap* map);
	MyMap* GetCurrentMap() { return m_currentMap; }

	void SetCurrentGround(MyMap* ground);
	MyMap* GetCurrentGround() { return m_currentGround; }

	void SetCurrentNPCLayer(MyMap* npcLayer);
	MyMap* GetCurrentNPCLayer() { return m_currentNPCLayer; }
	// view들
	CGyunityMapToolView* m_mainView = nullptr;
	MapManagerView* m_mapManagerView = nullptr;
	MapBrushView* m_mapBrushView = nullptr;
	NPCManagerView* m_npcManagerView = nullptr;
	// 기본 타일
	Tile* m_baseTile = nullptr;
	Tile* m_groundBaseTile = nullptr;
	Tile* m_npcBaseTile = nullptr;
private:


	DataControl* m_dataControl;
	MyMap* m_currentMap = nullptr;
	MyMap* m_currentGround = nullptr;
	MyMap* m_currentNPCLayer = nullptr;
	// end my code

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
