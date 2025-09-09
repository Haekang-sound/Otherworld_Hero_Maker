#include "pch.h"
#include "DataControl.h"
#include "ExtractedSprite.h"
#include "Sprite.h"
#include "GyunityView.h"
#include "SpriteInfoView.h"
#include "SpriteAnimation.h"

DataControl::DataControl()
{

}

DataControl::~DataControl()
{

}

void DataControl::SaveSpriteData(const CString& filePath)
{
	/// 0d 0a

	std::wofstream ofs;
	ofs.open(filePath);
	ofs << m_extractedSprites.size() << std::endl;
	for (const auto& curSprite : m_extractedSprites)
	{
		ofs << curSprite->Name << ',';
		ofs << curSprite->Left << ',';
		ofs << curSprite->Top << ',';
		ofs << curSprite->Right << ',';
		ofs << curSprite->Bottom << ',';
		ofs << curSprite->PivotX << ',';
		ofs << curSprite->PivotY << ',';
		ofs << std::endl;
	}
	ofs.close();

	return;
}

void DataControl::LoadSpriteData(const CString& filePath)
{
	// 스프라이트 개수
	int count = 0;
	std::wifstream ifs;
	ifs.open(filePath);
	ifs >> count;
	for (int i = 0; i < count; i++)
	{
		// 데이터
		std::wstring data;
		ifs >> data;
		ExtractedSprite* newSprite = new ExtractedSprite();

		// 데이터 타입을 정할떄 필요한 인덱스, 사실 하드 코딩에 가까움
		int dataIndex = 0;

		// 데이터 모음 중 하나의 데이터
		std::wstring one;
		for (int idx = 0; idx < data.size(); idx++)
		{
			if (data[idx] == ',')
			{
				switch (dataIndex)
				{
				case 0:
					// wstring 타입
					newSprite->Name = one;
					break;
				case 1:
					// float 타입으로 변환.
					newSprite->Left = stof(one);
					break;
				case 2:
					newSprite->Top = stof(one);
					break;
				case 3:
					newSprite->Right = stof(one);
					break;
				case 4:
					newSprite->Bottom = stof(one);
					break;
				case 5:
					newSprite->PivotX = stof(one);
					break;
				case 6:
					newSprite->PivotY = stof(one);
					break;
				default:
					break;
				}

				one = std::wstring();
				dataIndex++;
				continue;
			}
			one += data[idx];
		}
		m_extractedSprites.push_back(newSprite);
	}

	ifs.close();
}

void DataControl::SaveAnimationData(const CString& filePath)
{
	std::wofstream ofs;
	ofs.open(filePath);
	ofs << m_animations.size() << std::endl;
	for (const auto& anim : m_animations)
	{
		ofs << anim->m_sprites.size() << std::endl;
		ofs << anim->m_name << std::endl;
		ofs << anim->m_delayTime << std::endl;
		for (const auto& curSprite : anim->m_sprites)
		{
			ofs << curSprite->Name << ',';
			ofs << curSprite->Left << ',';
			ofs << curSprite->Top << ',';
			ofs << curSprite->Right << ',';
			ofs << curSprite->Bottom << ',';
			ofs << curSprite->PivotX << ',';
			ofs << curSprite->PivotY << ',';
			ofs << std::endl;
		}
	}
	ofs.close();
}

void DataControl::LoadAnimationData(const CString& filePath)
{
	ClearAnimations();
	// 애니메이션의 개수
	int animCount = 0;

	std::wifstream ifs;
	ifs.open(filePath);
	ifs >> animCount;

	for (int i = 0; i < animCount; i++)
	{
		// 현재 애니메이션의 스프라이트 개수
		int spriteCount = 0;
		ifs >> spriteCount;
		SpriteAnimation* loadAnimation = new SpriteAnimation();
		ifs >> loadAnimation->m_name;
		ifs >> loadAnimation->m_delayTime;
		for (int j = 0; j < spriteCount; j++)
		{
			// 데이터
			std::wstring data;
			ifs >> data;
			ExtractedSprite* newSprite = new ExtractedSprite();

			// 데이터 타입을 정할떄 필요한 인덱스, 사실 하드 코딩에 가까움
			int dataIndex = 0;

			// 데이터 모음 중 하나의 데이터
			std::wstring one;
			for (int idx = 0; idx < data.size(); idx++)
			{
				if (data[idx] == ',')
				{
					switch (dataIndex)
					{
					case 0:
						// wstring 타입
						newSprite->Name = one;
						break;
					case 1:
						// float 타입으로 변환.
						newSprite->Left = stof(one);
						break;
					case 2:
						newSprite->Top = stof(one);
						break;
					case 3:
						newSprite->Right = stof(one);
						break;
					case 4:
						newSprite->Bottom = stof(one);
						break;
					case 5:
						newSprite->PivotX = stof(one);
						break;
					case 6:
						newSprite->PivotY = stof(one);
						break;
					default:
						break;
					}

					one = std::wstring();
					dataIndex++;
					continue;
				}
				one += data[idx];
			}
			loadAnimation->m_sprites.push_back(newSprite);
		}
		m_animations.push_back(loadAnimation);
	}

	ifs.close();
}

void DataControl::SaveAnimationOneData(const CString& filePath, int idx)
{
	SpriteAnimation* saveAnim = m_animations[idx];

	std::wofstream ofs;
	ofs.open(filePath);

	ofs << saveAnim->m_sprites.size() << std::endl;
	for (const auto& curSprite : saveAnim->m_sprites)
	{
		ofs << curSprite->Name << ',';
		ofs << curSprite->Left << ',';
		ofs << curSprite->Top << ',';
		ofs << curSprite->Right << ',';
		ofs << curSprite->Bottom << ',';
		ofs << curSprite->PivotX << ',';
		ofs << curSprite->PivotY << ',';
		ofs << std::endl;
	}

	ofs.close();
}

void DataControl::ClearAnimations()
{
	for (auto& anim : m_animations)
	{
		delete anim;
		anim = nullptr;
	}
	m_animations.clear();
}
