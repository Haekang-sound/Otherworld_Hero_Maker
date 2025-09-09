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

	// 타일맵을 생성한다.
	//void CreateTileMap(int col, int row);
	void ReadSource(std::string tileSource);
	std::vector<int> SplitPush(std::string source);
	
private:
	// int 벡터의 배열
	std::vector<int> m_tileRow;
	std::vector<std::vector<int> > m_TileMap;
	
	/*-----배열정보를 받게되면 필요없어질 내용-------*/
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

	// 타일 출력을 위한 비트맵 정보
	Graphics::Sprite* tile;
	ID2D1Bitmap* tileBitmap;

	// 게임엔진이다? 잘 몰름
	GameEngine* m_gameEngine;

	// 타일맵 행렬
	int m_col;
	int m_row;
};