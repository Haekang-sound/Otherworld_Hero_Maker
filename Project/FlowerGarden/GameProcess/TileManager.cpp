#include "TileManager.h"
#include "ResourceManager.h"
#include "GameEngine.h"
#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "DebugManager.h"
// ���� �б�� ���
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

TileManager::TileManager(GameEngine* _gameEngine, DirectY* directY)
	: m_cManager(_gameEngine->GetCollisionManager())
	, m_gameEngine(_gameEngine)
	, m_tileMap{}
	, m_posVector{}, m_posVectors{}
	, m_stringVector{}, m_stringVectors{}
	, m_colliders{}
	, m_tileBitmap(_gameEngine->GetImage("TileExample"))
	, m_tile(nullptr)
	, m_colliderCount(0)
{
	m_tile = directY->ReadSpriteTxtFile("TileExample", m_tileBitmap);
	// ������ �о Ÿ������ �о����
	//ReadSource2("TestCheck");
}

TileManager::~TileManager()
{
	// Ÿ���� �����Ѵ�.
	delete m_tile;
}

void TileManager::Init()
{
	//Graphics::BaseFigure::Point center = { (float)(960), (float)(540 - (m_col * 36)) };
	Graphics::BaseFigure::Point center = { 72, 108 };
	// Ÿ�϶����� �׸��� ���� ����ü
	Graphics::BaseFigure::IsomatricTile nowCenter;

	for (int i = 0; i < m_size; i++)
	{
		// ������
		for (int j = 0; j < m_size; j++)
		{
			nowCenter = { (center.x + (72 * j)),(center.y + (36 * j)) };
			switch ((int)m_tileMap[i][j]%2)
			{
			case(0):
				break;
			case(1):
				Collider* collider = GetCManager()->
					CreateIsometricCollider(
						nowCenter.centerXY.x, 
						nowCenter.centerXY.y, 72);
				GetCManager()->AddCollider(	m_gameObject, collider);
				m_colliderCount++;
				break;
			}
			// ���� ��ġ�� �ٲ��ش�.

			// Ÿ�� ��ġ�� �����Ѵ�.
			m_posVector.push_back(nowCenter.centerXY);
		}
		// �� ���� ��ġ������ ���� ���͸� 2���� ���Ϳ� ��´�.
		m_posVectors.push_back(m_posVector);
		// �� ���� ��������Ʈ������ ���� ���͸� 2���� ���Ϳ� ��´�.
		m_stringVectors.push_back(m_stringVector);
		// �� ���� ���͸� �ʱ�ȭ���ش�.
		m_posVector.clear();
		center = { center.x - 72 , center.y + 36 };
	}
	
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
	//return;
	//Graphics::BaseFigure::Point center = { (float)(960), (float)(540 - (m_col * 36)) };
	Graphics::BaseFigure::Point center = { 72, 108 };
	// Ÿ�϶����� �׸��� ���� ����ü
	Graphics::BaseFigure::IsomatricTile nowCenter;

	// ���ο�
	for (int i = 0; i < m_size; i++)
	{
		// ������
		for (int j = 0; j < m_size; j++)
		{
			/// ���α׸���
			// �迭�� ���뿡 ���� ������ �����Ѵ�.
			switch ((int)m_tileMap[i][j])
			{
			case(0):
				directY->SetBrushColor(D2D1::ColorF::Gray);
				break;
			case(1):
				directY->SetBrushColor(D2D1::ColorF::Green);

				if (DebugManager::GetInstance().GetTileDebuging())
				{
					nowCenter = { (center.x + (72 * j)),(center.y + (36 * j)) };
					directY->DrawIsometric(nowCenter, 8);
				}

				break;
			}
			// ���� ��ġ�� �ٲ��ش�.
			//nowCenter = { (center.x + (72 * j)),(center.y + (36 * j)) };
			// �� ���� ��ġ������ ���Ϳ� ��´�.
			// Ÿ���� �׸���.

			/// Ÿ�ϱ׸���
			// ���� ������ġ�� �����Ѵ�.
			m_tile->m_drawPos = { nowCenter.centerXY.x - 72, nowCenter.centerXY.y - 36 };
			// �迭�� ���뿡 ���� Ÿ�� ���� ���� �� ���θ� �����Ѵ�.
			switch ((int)m_tileMap[i][j]%2)
			{
			case(0):
				break;
			case(1):
				directY->DrawBitmap(m_tile, 1.f);
				break;
			default:
				break;
			}
		}
		center = { center.x - 72 , center.y + 36 };
	}
}


void TileManager::PostRender(DirectY* directY)
{

}


void TileManager::Release()
{
// 	// �ݶ��̴��� �����Ѵ�
// 	for (int i = 0; i < m_colliderCount; i++)
// 	{
// 		m_cManager->DeleteCollider(m_gameObject);
}
// 	}

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
	std::ifstream resourceTextFile("Resource/Text/" + tileSource + ".txt");
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
				//m_col = stoi(source.substr(1));
			}
			else if (sourceType._Equal("row"))
			{
				source = infoLine.substr(infoLine.find(" "), infoLine.size());
				//m_row = stoi(source.substr(1));
			}
			else if (infoLine._Equal(""))
			{
				break;
			}
			else if(!infoLine._Equal(tileSource))
			{
				// 4. ����� ������ ���� ������ �Է��Ѵ�.
				m_tileMap.push_back(SplitPush(infoLine));
			}
		}
		resourceTextFile.close();
	}
	else
	{
		std::cout << "���� ���� ����";
	}
}

void TileManager::ReadSource2(std::string path)
{
	std::wifstream ifs;
	ifs.open(path);

	std::wstring mapName;
	ifs >> mapName;
	std::wstring temp;
	float size;
	ifs >> temp >> temp >> temp >> size;

	m_size = static_cast<int>(size);
	m_tileMap = std::vector<std::vector<int>>(m_size, std::vector<int>(m_size));

	//MyMap* newMap = new MyMap();
	//newMap->SetName(mapName);
	//newMap->CreateMap(size, size);

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			//int idx = y * size + x;
			/*ifs >> newMap->GetWorldData()[idx];*/
			ifs >> m_tileMap[y][x];

		}
	}

	ifs.close();
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

