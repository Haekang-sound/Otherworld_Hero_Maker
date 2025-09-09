#pragma once
#include <vector>
#include "../DirectY/DirectY.h"
#include "../GameEngine/ElementBase.h"


class ResourceManager;
class GameEngine;

class TileManager : public ElementBase
{
public:
	TileManager(GameEngine* _gameEngine, DirectY* directY);
	~TileManager();

	/*------------------------------------------------------------*/
	virtual void Init() override;

	virtual void FixedUpdate() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;

	virtual void PreRender() override;
	virtual void Render(DirectY* directY) override;
	virtual void PostRender() override;

	virtual void Release() override;

	virtual ElementType GetElementType() const override;

	virtual GameObject* GetGameObject() const override;
	virtual void SetGameObject(GameObject* gameObject) override;
	/*------------------------------------------------------------*/

	// Ÿ�ϸ��� �����Ѵ�.
	//void CreateTileMap(int col, int row);
	void ReadSource(std::string tileSource);
	std::vector<int> SplitPush(std::string source);
	
private:
	// int ������ �迭
	std::vector<int> m_tileRow;
	std::vector<std::vector<int> > m_TileMap;
	
	/*-----�迭������ �ްԵǸ� �ʿ������ ����-------*/
	int TileArr[6][4] =	{
							{1, 1, 1, 1},
							{1, 0, 1, 0},
							{1, 1, 0, 1},
							{1, 1, 1, 0},
							{1, 1, 1, 0},
							{1, 1, 1, 0}
						};
	int(*p)[4] = TileArr;
	/*--------------------------------------------*/

	// Ÿ�� ����� ���� ��Ʈ�� ����
	Graphics::Sprite* tile;
	ID2D1Bitmap* tileBitmap;

	// ���ӿ����̴�? �� ����
	GameEngine* m_gameEngine;

	// Ÿ�ϸ� ���
	int m_col;
	int m_row;
};