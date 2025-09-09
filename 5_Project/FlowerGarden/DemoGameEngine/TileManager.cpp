#include "TileManager.h"
#include "ResourceManager.h"
#include "GameEngine.h"
// 파일 읽기용 헤더
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

TileManager::TileManager( GameEngine* gameEngine, DirectY* directY)
{
	// 벡터 초기화
	m_tileRow.clear();
	m_TileMap.clear();

	// 타일 비트맵을 로딩한다. 씬리소스로딩으로 옮긴다.
	tileBitmap = gameEngine->GetImage("TileExample");

	// 타일비트맵 이미지를 sprite로 변환해서 저장한다.
	tile = directY->ReadSpriteTxtFile("Tile_Black", tileBitmap);

	// 파일을 읽어서 타일정보 읽어오기
	ReadSource("TileSource");
}

TileManager::~TileManager()
{
	// 타일을 삭제한다.
	delete tile;
}

void TileManager::Init()
{

}

void TileManager::FixedUpdate()
{

}

void TileManager::Update(float deltaTime)
{

}

void TileManager::LateUpdate()
{

}

void TileManager::PreRender()
{

}

void TileManager::Render(DirectY* directY)
{
	// 시작점,,
	// x = 해상도의 1/2, y = 0에 맞춰서
	// (였으면 좋겠다.)
	Graphics::BaseFigure::Point center = { (float)(960), (float)(540-(m_col * 36))};
	// 타일라인을 그리기 위한 구조체
	Graphics::BaseFigure::IsomatricTile nowCenter;
	
	// 세로열
	for (int i = 0; i < (int)m_TileMap.size(); i++)
	{
		// 가로행
		for (int j = 0; j < (int)m_TileMap[0].size(); j++)
		{
			/// 라인그리기
			// 배열의 내용에 따라 색상을 변경한다.
			switch (m_TileMap[i][j])
			{
			case(0):
				directY->SetBrushColor(D2D1::ColorF::White);
				break;
			case(1):
				directY->SetBrushColor(D2D1::ColorF::Green);
				break;
			}
 			// 현재 위치를 바꿔준다.
			nowCenter = { (center.x + (72 * j)),(center.y + (36 * j)) };
 			// 타일을 그린다.
 			directY->DrawIsometric(nowCenter, 8);
			
			/// 타일그리기
			// 파일 생성위치를 지정한다.
			tile->m_drawPos = { nowCenter.centerXY.x - 72, nowCenter.centerXY.y - 36 };
			// 배열의 내용에 따라 타일 생성 종류 및 여부를 결정한다.
			switch (m_TileMap[i][j])
			{
			case(0):
				break;
			case(1):
				directY->DrawBitmap(tile, 1.f);
				break;
			default:
				break;
			}
		}
		center = { center.x - 72 , center.y + 36 };
	}
}

void TileManager::PostRender()
{

}


void TileManager::Release()
{

}

/// <summary>
/// 타일맵의 elementype을 반환한다.
/// </summary>
/// <returns></returns>
ElementType TileManager::GetElementType() const
{
	return ElementType::Script;
}

/// <summary>
/// 타일맵의 오브젝트를 갖고있는 오브젝트를 반환한다.
/// </summary>
/// <returns></returns>
GameObject* TileManager::GetGameObject() const
{
	return m_gameObject;
}

/// <summary>
/// 타일맵의 오브젝트를 설정한다.
/// </summary>
/// <param name="gameObject"></param>
void TileManager::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

void TileManager::ReadSource(std::string tileSource)
{
	// 1. 파일명을 입력받고 파일명.text 파일을 연다
	std::ifstream resourceTextFile(tileSource + ".txt");
	std::string infoLine;
	// 파일이 열려있는지 확인한다.
	if(resourceTextFile.is_open())
	{
		// 2. 파일을 한 줄 씩 읽는다
		while (std::getline(resourceTextFile, infoLine))
		{
			// 3. 원하는 정보를 추출한다.
			std::string sourceType = infoLine.substr(0,3);
			std::string source;
			if (sourceType._Equal("col"))
			{
				source = infoLine.substr(infoLine.find(" "), infoLine.size());
				m_col = stoi(source.substr(1));
			}
			else if (sourceType._Equal("row"))
			{
				source = infoLine.substr(infoLine.find(" "), infoLine.size());
				m_row = stoi(source.substr(1));
			}
			else if (infoLine._Equal(""))
			{
				break;
			}
			else if(!infoLine._Equal(tileSource))
			{
				static int i = 0;
				// 4. 추출된 정보를 내부 변수에 입력한다.
				m_TileMap.push_back(SplitPush(infoLine));
				i++;
			}
		}
	}
	else
	{
		std::cout << "파일 오픈 실패";
	}
}

std::vector<int> TileManager::SplitPush(std::string source)
{
	
	// 스트링스트림에 소스 입력
	std::stringstream fullSource(source);
	std::string temp;
	std::vector<int> TileRow;
	while (std::getline(fullSource, temp, ' '))
	{
		TileRow.push_back(stoi(temp));
	}
	
	return TileRow;
}

