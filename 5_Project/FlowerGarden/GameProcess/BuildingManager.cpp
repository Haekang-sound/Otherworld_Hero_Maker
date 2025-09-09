#include "BuildingManager.h"
#include "GameEngine.h"

BuildingManager::BuildingManager(GameEngine* gameEngine, DirectY* directY)
	: m_building(nullptr),
	m_buildingBitmap(gameEngine->GetImage("testBuilding")),
	m_buildingMap{}
{
	m_building = directY->ReadSpriteTxtFile("testBuilding", m_buildingBitmap);
}

BuildingManager::~BuildingManager()
{
	delete m_building;
}

void BuildingManager::Init()
{

}

void BuildingManager::FixedUpdate()
{

}

void BuildingManager::Update(float deltaTime)
{

}

void BuildingManager::LateUpdate()
{

}

void BuildingManager::PreRender()
{

}

void BuildingManager::Render(DirectY* directY)
{

	Graphics::BaseFigure::Point center =
	{ (float)(960), (float)(540 - (24 * 36)) };
	// Ÿ�϶����� �׸��� ���� ����ü
	Graphics::BaseFigure::IsomatricTile nowCenter;
	
	for (int i = 0; i < 24; i++)
	{
		// ������
		for (int j = 0; j < 24; j++)
		{
			nowCenter = { (center.x + (72 * j)),(center.y + (36 * j)) };
			m_building->m_drawPos = { nowCenter.centerXY.x - 72, nowCenter.centerXY.y - 176 };
			if (m_buildingMap[i][j] == 3)
			{
				directY->DrawBitmap(m_building);
			}
			// ���� ��ġ�� �ٲ��ش�.
		}
		center = { center.x - 72 , center.y + 36 };
	}
}

void BuildingManager::PostRender(DirectY* directY)
{

}

void BuildingManager::Release()
{

}

ElementType BuildingManager::GetElementType() const
{
	return ElementType::Script;
}

GameObject* BuildingManager::GetGameObject() const
{
	return m_gameObject;
}

void BuildingManager::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}
