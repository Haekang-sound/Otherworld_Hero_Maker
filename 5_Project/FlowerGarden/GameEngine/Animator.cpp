#include "Animator.h"
#include "../DirectY/DirectY.h"

#include "Transform.h"
#include "GameObject.h"
#include "../GameProcess/SkinHeadNPC.h"

Animator::Animator() : ElementBase(), m_motionMap(NULL), m_motionIndex(0), m_currentMotion("link")
{
}

Animator::~Animator()
{
	Release();
}

void Animator::Init()
{

}

void Animator::FixedUpdate()
{

}

/// <summary>
/// ������Ʈ�ϸ鼭 � ����� ���� �������ش�
/// </summary>
/// <param name="deltaTime"></param>
void Animator::Update(float deltaTime)
{
	//�ٲ������ Ȯ���� ���� ���� ����� ������ ����
	std::string prevMotion = m_currentMotion;

	//�׽�Ʈ��
	//Ű�Է¿� ���� � �������� ������ � ����� ���� ���Ѵ�
	//if(InputManager::GetInstance().IsGetKeyDown(VK_UP/*test*/))
	//{
	//	if (prevMotion == m_currentMotion/*�ٲ��*/)
	//	{
	//		m_motionIndex = 0;	//����� �ٲ�鼭 �ٸ� �ִϸ��̼� ó�������ؾߵȴ�
	//		m_currentMotion = "test";	//key���� �ٲ۴�
	//	}
	//}

	int totalFrame = GetMotion(m_currentMotion)->GetTotalFrame();

	//static float totalTime = 0;
	//totalTime += deltaTime;

	m_totalTime += deltaTime;

	//�ð��� �����ɶ����� Ư���ð�(delayTime)���� index�� �ٲ� ��������Ʈ ��ü
	if (m_totalTime > m_delayTime/*GetMotion(m_currentMotion)->GetSprite(m_motionIndex)->m_delayTime*/)
	{
		if (m_motionIndex >= totalFrame-1)
		{
			m_motionIndex = 0;
		}
		else
		{
			m_motionIndex++;
		}

		m_totalTime = 0;
	}
}

void Animator::LateUpdate()
{

}

void Animator::PreRender()
{
	
}

void Animator::Render(DirectY* directY)
{
	// ���� ũ���� ���̶��
	SkinHeadNPC* temp = ((SkinHeadNPC*)(m_gameObject->GetElement(ElementType::Script)));

	if (temp->GetCurState() == SkinHeadNPC::State::Credit)
	{
		directY->SetTransform(((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->GetTransformMatrix());
	}

	directY->DrawBitmap(GetMotion(m_currentMotion)->GetSprite(m_motionIndex));
}

void Animator::PostRender(DirectY* directY)
{
	//�׸��� �� �׸��� ����Ʈ ������
}

void Animator::Release()
{
	for (auto& motion : m_motionMap)
	{
		delete motion.second;
	}
	m_motionMap.clear();
}

ElementType Animator::GetElementType() const
{
	return ElementType::Animator;
}

GameObject* Animator::GetGameObject() const
{
	return m_gameObject;
}

void Animator::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

/// <summary>
/// ����� ����� �ִϸ����Ϳ� �����Ѵ�
/// �ݵ�� �׷��Ƚ��������� ReadTextFile�Լ��� ��ǿ� sprite ������ motion�� �� ��
/// </summary>
/// <param name="motionName">key ��</param>
/// <param name="motion">value ��</param>
void Animator::AddMotion(std::string motionName, Graphics::Motion* motion)
{
	m_motionMap.insert({ motionName, motion });
}
