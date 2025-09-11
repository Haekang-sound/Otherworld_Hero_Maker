#pragma once



// AnimationInfoView 폼 보기

class AnimationInfoView : public CFormView
{
	DECLARE_DYNCREATE(AnimationInfoView)

protected:
	AnimationInfoView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~AnimationInfoView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	// my code
private:
	bool AddAnimation();
	void LoadAnimation();

	bool EditAnimation();

	// 현재 선택된 애니메이션의 인덱스를 불러온다.
	int GetAnimationIndex();

	std::wstring m_currentAnimName;
	int m_currentAnimDelayTime;
	int m_animationCount = 0;
	// end my code
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_animationList;
	afx_msg void OnBnClickedAddAnimation();
	afx_msg void OnBnClickedDeleteAnimation();
	afx_msg void OnBnClickedSaveAnimation();
	afx_msg void OnBnClickedLoadAnimation();
	afx_msg void OnLbnSelchangeAnimationList();
	afx_msg void OnBnClickedEditAnimation();
	afx_msg void OnBnClickedSaveAnimationOne();
};


