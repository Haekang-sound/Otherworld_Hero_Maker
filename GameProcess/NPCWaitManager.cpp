#include "NPCWaitManager.h"
#include "SkinHeadNPC.h"
#include "NpcManager.h"

NPCWaitManager::NPCWaitManager(NpcManager* npcManager)
	: m_npcManager(npcManager), m_npcList{}, m_waitQueue{}
{
	// ��� npc�� ������ �޾ƿ´�.
	m_npcList = m_npcManager->GetNpcs();
}

NPCWaitManager::~NPCWaitManager()
{
	
}

void NPCWaitManager::Init()
{

}

void NPCWaitManager::FixedUpdate()
{

}

void NPCWaitManager::Update(float deltaTime)
{
	CheckCollision();
}

void NPCWaitManager::LateUpdate()
{

}

void NPCWaitManager::PreRender()
{

}

void NPCWaitManager::Render(DirectY* directY)
{

}

void NPCWaitManager::PostRender(DirectY* directY)
{

}

void NPCWaitManager::Release()
{

}

ElementType NPCWaitManager::GetElementType() const
{
	return ElementType::Script;
}

GameObject* NPCWaitManager::GetGameObject() const
{
	return m_gameObject;
}

void NPCWaitManager::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

void NPCWaitManager::SetWaitNumber(SkinHeadNPC* waitingNpc)
{
	waitingNpc->SetWaitNumber(m_npcList.size());
}

/// <summary>
/// npc�� �浹���¸� Ȯ���ϰ�
/// �浹���� ��� queue�� �߰�,
/// ����ȣ�� �߰��Ѵ�.
/// </summary>
void NPCWaitManager::CheckCollision()
{
	static int num = 0;
	// npc�� �浹���¸� Ȯ���Ѵ�.
	for (int i = 0; i < (int)m_npcList.size(); i++)
	{
		// npc�� �浹�Ѱ��
		if (m_npcList[i]->GetTakeTicket())
		{
			// ����ϰ� �ִ� npc�� 4�� �̸��� ���
			if(m_waitQueue.size() < 4)
			{
				// ��⿭�� �ش� npc�� �߰��ϰ� 
				// ���ѹ��� �ο���
				m_waitQueue.push(m_npcList[i]);
				m_npcList[i]->SetWaitNumber(m_waitQueue.size());
			}
			// ��� ���� npc�� 4�� �̻��� ���
			else
			{
				// ��⿭�� �߰����� ����
				// number5�� �ο���
				m_npcList[i]->SetWaitNumber(5);
				m_npcList[i]->SetIsAccident(true);
			}
		}
		m_npcList[i]->SetTakeTicket(false);
	}
}

void NPCWaitManager::isPoP()
{
	// npc�� �����¸� Ȯ���Ѵ�.
	for (int i = 0; i < (int)m_npcList.size(); i++)
	{
		// npc�� ������� ���
		if (m_npcList[i]->GetIsWaiting())
		{
			// �� ���� ��
			if(m_npcList[i]->GetWaitNumber() == 1)
			{
				m_npcList[i]->SetWaitNumber(-1);
				m_npcList[i]->SetIsInterview(true);

				m_npcList[i]->SetIsWaiting(false);
				m_npcList[i]->SetIsInterviewExit(true);
			}
			else if (m_npcList[i]->GetWaitNumber() > 1 && m_npcList[i]->GetWaitNumber() <= 4)
			{
				m_npcList[i]->SetWaitNumber(m_npcList[i]->GetWaitNumber() - 1);
			}
		}
	}
}
