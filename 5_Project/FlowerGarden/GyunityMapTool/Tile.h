#pragma once
#include "Sprite.h"

class Tile : public Sprite
{
public:
	Tile();
	virtual ~Tile();

	std::wstring GetName() const { return m_name; }
	void SetName(std::wstring val) { m_name = val; }

	
	CString GetFilePath() const { return m_filePath; }
	void SetFilePath(CString val) { m_filePath = val; SetRelativePath(val); }

	void SetRelativePath(CString val);
	std::wstring GetRelativePath() const { return m_relativePath; }
	int GetNpcID() const { return m_npcId; }
	void SetNpcID(int val) { m_npcId = val; }
private:
	std::wstring m_name;
	CString m_filePath;
	std::wstring m_relativePath;

	int m_npcId = 0;
};

