#pragma once
#include "ElementBase.h"
#include "Vector2.h"
#include <vector>
// test
#include <functional>
#include <string>



namespace Graphics { struct Sprite; }
namespace Graphics { class Motion; }
namespace Algorithm { class FindPosition; }

class Transform;
class AudioSource;

class Player : public ElementBase
{
public:
	Player();
	~Player();

	/// Override
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

	/// Move
	Transform* GetMyTransform() const { return m_transform; }
	void SetMyTransform(Transform* val) { m_transform = val; }

	float GetSpeed() const { return m_speed; }
	void SetSpeed(float val) { m_speed = val; }

	float GetDegree() const { return m_degree; }
	void SetDegree(float val) { m_degree = val; }

	MathEngine::Vector2 GetDirectionVecter() const { return m_directionVector; }
	void SetDirectionVecter(MathEngine::Vector2 val) { m_directionVector = val; }

	void VectorToDirection();
	void DirectionToVector();

	bool GetStun() const { return m_isStun; }
	void SetStun(bool isStun); 

	// Render
	void SetMotion(Graphics::Motion* truckMotion) { m_truckMotion = truckMotion; }

	void SetMyPaticle(Graphics::Sprite* paticle) { m_myPaticle = paticle; }
	void SetMyPaticle2(Graphics::Sprite* paticle) { m_myPaticle2 = paticle; }

	MathEngine::Vector2 GetMoveVector() const { return m_moveVector; }
	void SetMoveVector(MathEngine::Vector2 val) { m_moveVector = val; }

	/*--------------------------------------------------------------------*/
	void SetAudioSource(AudioSource* audioSource) { m_audioSource = audioSource;}
	
	void BeCaught();

private:
	Transform* m_transform;
	AudioSource* m_audioSource;

	float m_acceleration; // Ʈ�� ���ӵ�
	float m_earlyAcceleration;
	float m_speed; // Ʈ�� �ӵ�
	const float m_minSpeed; // speed 0 ���� �����̱� ������ �� ������ �ӵ�
	float m_damping; // ���� ���

	/// ���� �浹 �� ���� ����
	bool m_isStun;
	float m_stunDelay;
	float m_stunSpeed; // stun �ɷ��� �� �ڷ� �����̴� �ӵ�

	/// ȸ�� ���� ���
	const float m_truckAngle; // Ʈ�� �ִϸ��̼� �� �� �� ����
	float m_rotationVelocity; // ȸ�� �ӷ�

	float m_degree; // ���� ����
	float m_direction; // ��������Ʈ�� ������ ��ġ��Ű�� ���� truckAngle�� ����� ������ ����
	MathEngine::Vector2 m_directionVector; // ������ ���ͷ� 
	MathEngine::Vector2 m_moveVector; // �浹�� �� ���� �ִ� ����� ������ �ðܳ��� ����

	/// Animation
	Graphics::Motion* m_truckMotion; 

	/// ��ƼŬ ����
	float m_deltaTime;
	float m_totalTime;
	bool m_paticleDelay;
	Graphics::Sprite* m_myPaticle;
	Graphics::Sprite* m_myPaticle2;

	/// Gyu code
	// ������ ��ġ�� ���� ���̾ �ٲٱ� ���� �Լ��� ���� ����
	void FindThisPositionAndSetLayer();
	Algorithm::FindPosition* m_findPosition;
	std::vector<std::vector<int>> m_layerArr
		= std::vector<std::vector<int>>(100,std::vector<int>(100));
	int m_tileLayer;
	int m_size;
	int m_currentLayer;
};