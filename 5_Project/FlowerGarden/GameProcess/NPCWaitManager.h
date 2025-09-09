#pragma once
#include <ElementBase.h>
#include <vector>
#include "queue"

class NpcManager;
class SkinHeadNPC;

class NPCWaitManager : public ElementBase
{
public:
	NPCWaitManager(NpcManager* npcManager);
	~NPCWaitManager();

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

	// npc�� ��⿭�� �����Ѵ�.
	void SetWaitNumber(SkinHeadNPC* waitingNpc);
	// �浹���¸� Ȯ��
	void CheckCollision();

	std::queue<SkinHeadNPC*>& GetWaitQueue() { return m_waitQueue; }
	void SetWaitQueue(std::queue<SkinHeadNPC*> val) { m_waitQueue = val; }

	void isPoP();

private:
	// npc���� �޾ƿ������� npc�Ŵ���
	NpcManager* m_npcManager;
	SkinHeadNPC* firstNpc = nullptr;

	// ���� �����ϴ� ��� npc
	std::vector<SkinHeadNPC*> m_npcList;
	
	// �����忡 �ִ� npc�� �����ϱ����� queue
	std::queue<SkinHeadNPC*> m_waitQueue;
};

