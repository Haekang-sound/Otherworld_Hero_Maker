#pragma once
#include "GyunityView.h"


// SpriteEditorView 폼 보기



class SpriteEditorView : public CFormView
{
	DECLARE_DYNCREATE(SpriteEditorView)

protected:
	SpriteEditorView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~SpriteEditorView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPRITE_EDIT };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	// my code
protected:
	//CGyunityView* m_mainView;
	CRenderTarget* m_rt;
	void LoadBitMapByFilePath(LPCTSTR filePath);
protected:
	//std::unordered_map<std::wstring, Sprite*> m_sprites;
	// end my code
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadbmpBtn();

	// type (auto, grid by cell size or count)
	CString m_typeInfo;
	virtual void OnInitialUpdate();

	/// <summary>
	/// SliceButton
	/// </summary>
	afx_msg void OnBnClickedSliceBtn();
	int m_cellColumn;
	int m_cellRow;
	float m_cellSizeX;
	float m_cellSizeY;
	float m_pivotX;
	float m_pivotY;
};


