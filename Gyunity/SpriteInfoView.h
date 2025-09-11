#pragma once



// SpriteInfoView 폼 보기

class SpriteInfoView : public CFormView
{
	DECLARE_DYNCREATE(SpriteInfoView)

protected:
	SpriteInfoView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~SpriteInfoView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SpriteInfo };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	// my Code
public:
	void GetSpriteInfo(ExtractedSprite* extractedSprite);
	ExtractedSprite* m_currentExtractedSprite = nullptr;

	// end my Code
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_spriteName;
	float m_spriteX;
	float m_spriteY;
	float m_spriteCx;
	float m_spriteCy;
	float m_spritePx;
	float m_spritePy;
	afx_msg void OnBnClickedSpriteApply();
//	virtual void Serialize(CArchive& ar);
};


