
// GyunityDoc.h: CGyunityDoc 클래스의 인터페이스
//


#pragma once


class CGyunityDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CGyunityDoc() noexcept;
	DECLARE_DYNCREATE(CGyunityDoc)

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
	virtual ~CGyunityDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

public:
	// my code

	// 모든 데이터를 관리할 함수와 클래스
	void SaveSpriteData(const CString& filePath);
	class DataControl* m_dataControl;

	// 메인 뷰에 보이는 스프라이트
	//Sprite* m_mainSprite = nullptr;
	// 메인 스프라이트의 이름
	//std::wstring m_mainSpriteName = {};
	// 추출한 스프라이트들
	//std::vector<ExtractedSprite*> m_extractedSprites;
	// 메인 뷰의 렌더 타겟
	CRenderTarget* m_rt;

	// 애니메이션 뷰의 렌더 타겟
	CRenderTarget* m_rtAnimationView;


	// 여러 스프라이트들을 저장할 용도로 만들긴 했는데 사실 잘 사용안해서 나중에 리팩토링해야 함
	//std::unordered_map<std::wstring, Sprite*> m_sprites;

	// 메인 뷰 클래스 (메인 이미지가 보이는)
	class CGyunityView* m_mainView;

	// 스프라이트의 정보를 보여줄 뷰 클래스
	class SpriteInfoView* m_spriteInfoView;
	
	// 애니메이션 뷰
	class AnimationView* m_animationView;
	// end my code
	 
	
// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
