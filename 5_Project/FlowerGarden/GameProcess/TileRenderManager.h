#pragma once
#include "ElementBase.h"
#include "../GameEngine/ElementBase.h"
#include "../DirectY/DirectY.h"

class ResourceManager;
class GameEngine;
struct Graphics::Sprite;
class Scene;
class GameObject;

enum class TileRenderState
{
	Ground,
	Zone,
	Object,
};

class TileRenderManager : public ElementBase
{
public:
	TileRenderManager(GameEngine* gameEngine, Scene* scene, DirectY* directY, TileRenderState state = TileRenderState::Ground);
	virtual ~TileRenderManager();

	/*------------------------------------------------------------*/
	virtual void Init() override;

	virtual void FixedUpdate() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;

	virtual void PreRender() override;
	virtual void Render(DirectY* directY) override;
	virtual void PostRender(DirectY* directY) override;

	virtual void Release() override;

	virtual ElementType GetElementType() const override;
	virtual GameObject* GetGameObject() const override;
	virtual void SetGameObject(GameObject* gameObject) override;
	/*------------------------------------------------------------*/

	/// <summary>
	/// �޾ƿ� Ÿ�ϵ��� �׸��ϴ�.
	/// </summary>
	void DrawTiles(DirectY* directY);

	/// <summary>
	/// �޾ƿ� Ÿ�ϵ��� �����մϴ�. (���̾� ����)
	/// </summary>
	void MakeTileObject();

	/// <summary>
	/// ������ ����� ������ �ҷ��´�.
	/// </summary>
	/// <param name="path"></param>
	void ReadSource(std::string path);

private:
	GameEngine* m_gameEngine;
	Scene* m_scene;
	DirectY* m_directY;
private:
	// Ÿ�� ������ ����
	std::vector<std::vector<int>> m_tiles;

	// Ÿ�� ��������Ʈ ������ ������ ���� // ���� �ε����� ���缭 ����� ��.
	std::vector<Graphics::Sprite*> m_tileSprites;

	// ��� ���� ���� ����� ������ �� ������ ������ ���ڴ�.
	int m_size;

	// Ÿ���� �⺻ ������
	const int m_tileHeight;
	const int m_tileWidth;

	Graphics::Motion* m_groundTileImages;
	Graphics::Motion* m_roadTileImages;
	Graphics::Motion* m_objectTileImages;
	Graphics::Motion* m_chairTileImages;
	Graphics::Motion* m_woodTileImages;
	Graphics::Motion* m_roadTile2Images;
	

	std::vector<Graphics::Sprite*> m_otherSprites;

	// Test ( ���̾ �ٸ��� �ؼ� ���ӿ�����Ʈ�� ���⼭ ������)
private:
	// ���� ��� ���� ���̾� �и��� ����� �����ϹǷ� �׳� �ѹ��� ����.
	
	bool m_ground = false;
	TileRenderState m_tileRenderState = TileRenderState::Ground;

	void MakeTile(float x, float y, int tileIdx, int tileLayer);
	int m_tileLayer = 0;

	// test
	std::vector<GameObject*> test;
	int TestCount = 0;

};

