#include "TileManager.h"
#include "ResourceManager.h"
#include "GameEngine.h"
// ���� �б�� ���
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

TileManager::TileManager( GameEngine* gameEngine, DirectY* directY)
{
	// ���� �ʱ�ȭ
	m_tileRow.clear();
	m_TileMap.clear();

	// Ÿ�� ��Ʈ���� �ε��Ѵ�. �����ҽ��ε����� �ű��.
	tileBitmap = gameEngine->GetImage("TileExample");

	// Ÿ�Ϻ�Ʈ�� �̹����� sprite�� ��ȯ�ؼ� �����Ѵ�.
	tile = directY->ReadSpriteTxtFile("Tile_Black", tileBitmap);

	// ������ �о Ÿ������ �о����
	ReadSource("TileSource");
}

TileManager::~TileManager()
{
	// Ÿ���� �����Ѵ�.
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
	// ������,,
	// x = �ػ��� 1/2, y = 0�� ���缭
	// (������ ���ڴ�.)
	Graphics::BaseFigure::Point center = { (float)(960), (float)(540-(m_col * 36))};
	// Ÿ�϶����� �׸��� ���� ����ü
	Graphics::BaseFigure::IsomatricTile nowCenter;
	
	// ���ο�
	for (int i = 0; i < (int)m_TileMap.size(); i++)
	{
		// ������
		for (int j = 0; j < (int)m_TileMap[0].size(); j++)
		{
			/// ���α׸���
			// �迭�� ���뿡 ���� ������ �����Ѵ�.
			switch (m_TileMap[i][j])
			{
			case(0):
				directY->SetBrushColor(D2D1::ColorF::White);
				break;
			case(1):
				directY->SetBrushColor(D2D1::ColorF::Green);
				break;
			}
 			// ���� ��ġ�� �ٲ��ش�.
			nowCenter = { (center.x + (72 * j)),(center.y + (36 * j)) };
 			// Ÿ���� �׸���.
 			directY->DrawIsometric(nowCenter, 8);
			
			/// Ÿ�ϱ׸���
			// ���� ������ġ�� �����Ѵ�.
			tile->m_drawPos = { nowCenter.centerXY.x - 72, nowCenter.centerXY.y - 36 };
			// �迭�� ���뿡 ���� Ÿ�� ���� ���� �� ���θ� �����Ѵ�.
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
/// Ÿ�ϸ��� elementype�� ��ȯ�Ѵ�.
/// </summary>
/// <returns></returns>
ElementType TileManager::GetElementType() const
{
	return ElementType::Script;
}

/// <summary>
/// Ÿ�ϸ��� ������Ʈ�� �����ִ� ������Ʈ�� ��ȯ�Ѵ�.
/// </summary>
/// <returns></returns>
GameObject* TileManager::GetGameObject() const
{
	return m_gameObject;
}

/// <summary>
/// Ÿ�ϸ��� ������Ʈ�� �����Ѵ�.
/// </summary>
/// <param name="gameObject"></param>
void TileManager::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

void TileManager::ReadSource(std::string tileSource)
{
	// 1. ���ϸ��� �Է¹ް� ���ϸ�.text ������ ����
	std::ifstream resourceTextFile(tileSource + ".txt");
	std::string infoLine;
	// ������ �����ִ��� Ȯ���Ѵ�.
	if(resourceTextFile.is_open())
	{
		// 2. ������ �� �� �� �д´�
		while (std::getline(resourceTextFile, infoLine))
		{
			// 3. ���ϴ� ������ �����Ѵ�.
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
				// 4. ����� ������ ���� ������ �Է��Ѵ�.
				m_TileMap.push_back(SplitPush(infoLine));
				i++;
			}
		}
	}
	else
	{
		std::cout << "���� ���� ����";
	}
}

std::vector<int> TileManager::SplitPush(std::string source)
{
	
	// ��Ʈ����Ʈ���� �ҽ� �Է�
	std::stringstream fullSource(source);
	std::string temp;
	std::vector<int> TileRow;
	while (std::getline(fullSource, temp, ' '))
	{
		TileRow.push_back(stoi(temp));
	}
	
	return TileRow;
}

