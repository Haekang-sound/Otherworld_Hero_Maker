#include "Player.h"

#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"

#include "InputManager.h"
#include "CameraManager.h"
#include "AudioSource.h"

#include "MathUtils.h"
#include "Constants.h"
#include <cmath>

//temp
#include "Sprite.h"
#include "DirectY.h"
#include "FindPosition.h"

#include <iostream>
//#include <vector>
#include <ctime>
#include <cstdlib>


// Debug
#include "DebugManager.h"

Player::Player()
	: m_acceleration(85) // ���ӵ�
	, m_earlyAcceleration(7) // �ʹ� ���� ����
	, m_speed(0)
	, m_rotationVelocity(330) // ȸ���ӵ�
	, m_damping(70) // ���� (��������, ������ �� �ð��� �����鼭 �ڵ����� �ӵ��� �������� ��)
	, m_degree(0)
	, m_direction(0)
	, m_truckAngle(11.25)
	, m_minSpeed(1)
	, m_deltaTime(0)
	, m_totalTime(0)
	, m_paticleDelay(false)
	, m_myPaticle(nullptr)
	, m_myPaticle2(nullptr)
	, m_isStun(false)
	, m_stunDelay(0)
	, m_stunSpeed(115) // Ŀ���� ƨ�ܳ����� �Ÿ��� �þ
	, m_truckMotion(nullptr)
	, m_moveVector({})
	, m_transform(nullptr)
	, m_audioSource(nullptr)
	, m_tileLayer(0)
	, m_size(100)
	, m_currentLayer(0)
{
	m_findPosition = new Algorithm::FindPosition();


	// gyu code
	m_findPosition->Init();
	MathEngine::Vector2 renderPos(0, 0);
	int prevY = 0;
	int prevX = 0;
	while (true)
	{
		int y = static_cast<int>(renderPos.y);
		int x = static_cast<int>(renderPos.x);

		if (renderPos.x == 0)
		{
			// Ÿ�� ���̾� ����
			m_tileLayer++;
		}

		if (renderPos.y == m_size - 1)
		{
			m_tileLayer++;
		}
		m_layerArr[y][x] = m_tileLayer;

		if (renderPos.x == m_size - 1 && renderPos.y == m_size - 1)
		{
			break;
		}

		if (renderPos.x == m_size - 1)
		{
			prevX++;
			renderPos.x = static_cast<float>(prevX);
			renderPos.y = static_cast<float>(prevY);
		}
		else if (renderPos.y == 0)
		{
			prevY++;
			renderPos.y = static_cast<float>(prevY);
			renderPos.x = 0;
		}
		else
		{
			renderPos.y -= 1;
			renderPos.x += 1;
		}

		if (renderPos.y > m_size - 1)
			renderPos.y--;
		if (renderPos.x > m_size - 1)
			renderPos.x--;
	}
}

Player::~Player()
{
	delete m_myPaticle;
	delete m_myPaticle2;

	delete m_truckMotion;
	delete m_findPosition;
}

void Player::Init()
{
	
}

void Player::FixedUpdate()
{

}

void Player::Update(float deltaTime)
{
	m_deltaTime = deltaTime;

	// ���� �����
	if (!(m_audioSource->isPlaying("sfx_engineSoundBase_loop")))
	{
		m_audioSource->PlayBack("sfx_engineSoundBase_loop", FMOD_LOOP_NORMAL);
	}
	// �������� ������ FADEOUT
	if ((InputManager::GetInstance().IsGetKeyUp('W') || InputManager::GetInstance().IsGetKeyUp(VK_UP)))
	{
		m_audioSource->FadeOut("sfx_engineSoundMId_loop",5);
	}

	if (m_isStun)
	{
		// �ε����� �� 
		if (!(m_audioSource->isPlaying("sfx_hit_wall_1")))
		{
			m_audioSource->PlayBack("sfx_hit_wall_1");
			// �����϶�������ϴ� �Ҹ���
			m_audioSource->StopSound("sfx_engineSoundMId_loop");
			m_audioSource->StopSound("sfx_engineSoundBase_loop");
			m_audioSource->StopSound("sfx_trucBack_loop");
		}

		if (m_stunSpeed > 0)
		{
			m_stunSpeed -= m_acceleration * deltaTime;
		}
		if (m_stunSpeed < 0)
		{
			m_stunSpeed += m_acceleration * deltaTime;
		}
		m_stunDelay += deltaTime;
		if (m_speed > 600)
		{
			if (m_stunDelay >= 0.5f) // ���� �ɸ��� �ð� ���� 0.5��
			{
				m_isStun = false;
				m_speed = 0;
				m_stunDelay = 0;
			}
		}
		else if (m_speed > 500)
		{
			if (m_stunDelay >= 0.3f) // ���� �ɸ��� �ð� ���� 0.5��
			{
				m_isStun = false;
				m_speed = 0;
				m_stunDelay = 0;
			}
		}
		else
		{
			if (m_stunDelay >= 0.05f) // ���� �ɸ��� �ð� ���� 0.5��
			{
				m_isStun = false;
				m_speed = 0;
				m_stunDelay = 0;
			}
		}
	}
	else
	{
		bool isCollision = ((Collider*)(m_gameObject->GetElement(ElementType::Collider)))->GetIsCollision();

		// ���� ��� ������
		if (InputManager::GetInstance().IsGetKeyDown(VK_UP) || InputManager::GetInstance().IsGetKeyDown('W'))
		{
 			//if (!(m_audioSource->isPlaying("sfx_truck_start")))
 			{
				m_audioSource->PlayBack("sfx_truck_start");
			}
		}

		// ����, ����
		if (InputManager::GetInstance().IsGetKey(VK_UP) || InputManager::GetInstance().IsGetKey('W'))
		{
			// �����Ҷ� ������
			if (!(m_audioSource->isPlaying("sfx_engineSoundMId_loop")))
			{
				m_audioSource->PlayBack("sfx_engineSoundMId_loop", 0.5f, FMOD_LOOP_NORMAL);
			}
			if (m_speed < m_minSpeed)
			{
				m_speed = m_minSpeed;
			}
			if (m_speed < 360) // �ʹ� ���ӵ� ����
			{
				m_speed += m_acceleration * m_earlyAcceleration * deltaTime;
			}
			else if (m_speed > 700) // �ְ� �ӵ� ����
			{

			}
			else
			{
				m_speed += m_acceleration * deltaTime;
			}
		}
		// ������ư ���� ��������
		if (InputManager::GetInstance().IsGetKeyUp(VK_DOWN) || InputManager::GetInstance().IsGetKeyUp('S'))
		{
			m_audioSource->StopSound("sfx_trucBack_loop");
		}

		if (InputManager::GetInstance().IsGetKey(VK_DOWN) || InputManager::GetInstance().IsGetKey('S'))
		{
			// �����Ҷ� ������
			if (!(m_audioSource->isPlaying("sfx_engineSoundMId_loop")))
			{
				m_audioSource->PlayBack("sfx_engineSoundMId_loop", 0.4f, FMOD_LOOP_NORMAL);
			}
			// ������ε�
			if (!(m_audioSource->isPlaying("sfx_trucBack_loop")))
			{
				m_audioSource->PlayBack("sfx_trucBack_loop", 0.3f, FMOD_LOOP_NORMAL);
			}
			if (m_speed > -360)
			{
				m_speed -= m_acceleration * 3 * deltaTime;
			}
			else if (m_speed < -600)
			{

			}
			else
			{
				m_speed -= m_acceleration * deltaTime;
			}
		}

		// 	//��Ʈ �ε��� * TruckAngle
		if ((4 * m_truckAngle < m_degree && m_degree <= 5 * m_truckAngle))
		{
			m_direction = 26.57f;
		}

		if ((20 * m_truckAngle < m_degree && m_degree <= 21 * m_truckAngle))
		{
			m_direction = 180 + 26.57f;
		}

		if (12 * m_truckAngle < m_degree && m_degree <= 13 * m_truckAngle)
		{
			m_direction = 180 - 26.57f;
		}

		if (28 * m_truckAngle < m_degree && m_degree <= 29 * m_truckAngle)
		{
			m_direction = -26.57f;
		}

		// ���� �߿��� ���� ���� X
		if (!InputManager::GetInstance().IsGetKey(VK_UP) && !InputManager::GetInstance().IsGetKey('W') &&
			!InputManager::GetInstance().IsGetKey(VK_DOWN) && !InputManager::GetInstance().IsGetKey('S'))
		{
			// ���� ����
			if (m_speed > 0)
			{
				m_speed -= m_damping * deltaTime * 5;
				if (m_speed < 0)
				{
					m_speed = 0;
				}
			}
			else
			{
				m_speed += m_damping * deltaTime * 5;
				if (m_speed > 0)
				{
					m_speed = 0;
				}
			}
		}
	}

	if (InputManager::GetInstance().IsGetKey(VK_LEFT) || InputManager::GetInstance().IsGetKey('A'))
	{
		SetDegree(GetDegree() - m_rotationVelocity * deltaTime);
		if (GetDegree() < 0)
		{
			SetDegree(360 + GetDegree());
		}

		m_direction = (int)(GetDegree() / m_truckAngle) * m_truckAngle;
	}
	if (InputManager::GetInstance().IsGetKey(VK_RIGHT) || InputManager::GetInstance().IsGetKey('D'))
	{
		SetDegree(GetDegree() + m_rotationVelocity * deltaTime);
		if (GetDegree() > 360)
		{
			SetDegree(m_degree - 360);
		}

		m_direction = (int)(m_degree / m_truckAngle) * m_truckAngle;
	}

	// ������ ���ͷ� ��ȯ�ؼ� ������ ����
	DirectionToVector();
	if (m_isStun)
	{
		m_transform->Translate(m_moveVector * m_stunSpeed * deltaTime);
	}
	else
	{
		m_transform->Translate(m_directionVector * m_speed * deltaTime);
	}

	Vector2 cameraScale = CameraManager::GetInstance().GetCameraScale();
	// Temp �ӽ� ī�޶� ����
	CameraManager::GetInstance().SetCameraPosition({ 
		( - m_transform->GetLocalPosition().x * cameraScale.x + 720),
		( - m_transform->GetLocalPosition().y * cameraScale.y + 540)
		});

	// �ö��̴� ����
	((Collider*)(m_gameObject->GetElement(ElementType::Collider)))->GetCollider()->m_degree = this->m_degree;

	/// ���� �ȵǴ� �ڵ�
}

void Player::LateUpdate()
{

}

void Player::PreRender()
{
	FindThisPositionAndSetLayer();
}

void Player::Render(DirectY* directY)
{
	for (int i = 0; i < 32; i++)
	{
		if (m_degree >= i * m_truckAngle && m_degree < (i + 1) * m_truckAngle)
		{
			m_transform->SetLocalScale({ 1, 1 });
			directY->DrawBitmap(m_truckMotion->GetSprite(i));
		}
	}

	directY->PaticeUpdate(m_deltaTime);
	if (((Collider*)(m_gameObject->GetElement(ElementType::Collider)))->GetIsCollision() == true)
	{
		if (!m_paticleDelay)
		{
			for (int i = 0; i < 20; ++i)
			{
				if (i % 2 == 0)
				{
					directY->SetPaticle({ 0,0 }, (float)(i % 2) + 1, i, m_myPaticle);
				}
				else
				{
					directY->SetPaticle({ 0,0 }, (float)(i % 2) + 1, i, m_myPaticle2);
				}
			}
			m_paticleDelay = true;
		}
	}

	directY->PaticleEffect(m_transform->GetScreenMatrix());
	m_transform->SetTransform(directY);

	m_totalTime += m_deltaTime;
	if (m_totalTime > 3)
	{
		m_paticleDelay = false;
		m_totalTime = 0;
	}
}

void Player::PostRender(DirectY* directY)
{
	if (DebugManager::GetInstance().GetIsDebuging())
	{
		directY->SetBrushColor(255, 255, 255, 255);
		directY->DrawText(0, 0, 20, TextAlignMent::LEFT, L"verdana", "X: %f", m_directionVector.x);
		directY->DrawText(0, 20, 20, TextAlignMent::LEFT, L"verdana", "Y: %f", m_directionVector.y);
		Vector2 curPosition = ((Transform*)(m_gameObject->GetElement(ElementType::Transform)))->GetLocalPosition();
		directY->DrawText(0, 40, 20, TextAlignMent::LEFT, L"verdana", "X: %f", curPosition.x);
		directY->DrawText(0, 60, 20, TextAlignMent::LEFT, L"verdana", "Y: %f", curPosition.y);
		directY->DrawText(0, 80, 20, TextAlignMent::LEFT, L"verdana", "layer: %d", m_currentLayer);
	}
}

void Player::Release()
{

}

ElementType Player::GetElementType() const
{
	return ElementType::Script;
}

GameObject* Player::GetGameObject() const
{
	return m_gameObject;
}

void Player::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

void Player::VectorToDirection()
{
	float radian = atan2(m_directionVector.y, m_directionVector.x);
	m_degree = MathEngine::RADIAN_TO_DEGREE(radian);
	if (GetDegree() <= 0)
	{
		SetDegree(360 + GetDegree());
	}
	if (GetDegree() >= 360)
	{
		SetDegree(m_degree - 360);
	}
	m_direction = (int)(m_degree / m_truckAngle) * m_truckAngle;
}

void Player::DirectionToVector()
{
	float radian = MathEngine::DEGREE_TO_RADIAN(m_direction);
	m_directionVector = { cos(radian), sin(radian) };
}

void Player::SetStun(bool isStun)
{
	m_isStun = isStun;
	if (m_speed > 600)
	{
		m_stunSpeed = 300;
	}
	else if (m_speed > 500)
	{
		m_stunSpeed = 200;
	}
}

void Player::BeCaught()
{
	m_gameObject->SetActive(false);
	m_gameObject->SetIsDraw(true);
}

void Player::FindThisPositionAndSetLayer()
{
	// �迭 ��ǥ, ������ ��ġ
	std::pair<MathEngine::Vector2, MathEngine::Vector2> getData
		= m_findPosition->FindNearest(m_transform->GetLocalPosition());
	
	m_currentLayer = m_layerArr[getData.first.x][getData.first.y];

	// ���⼭ ���̾� ����
	m_transform->SetLayer(m_currentLayer + 1);
}

