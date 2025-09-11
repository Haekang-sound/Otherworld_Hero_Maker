#pragma once
#include "NPC.h"

#include "Vector2.h"

#include <iostream>
#include <string>
#include <vector>

class FSM;
class Transform;
class AudioSource;

namespace Graphics { class Motion; }
namespace Algorithm { class PathFinding; }

class GameObject;

class Police : public NPC
{
public:
	Police(Transform* playerTransform, Transform* policeTrasform, const MathEngine::Vector2 policeStation, std::string mapDataPath, std::vector<MathEngine::Vector2> patrolPath);
	~Police();

	enum class State
	{
		Idle, // ��һ���
		Chasing, // �÷��̾� �߰� ��
		Collision // �÷��̾ ����� ��
	};

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

	void SetPolice(Graphics::Motion* motion) { m_police = motion; };
	void SetRedPolice(Graphics::Motion* motion) { m_redPolice = motion; };
	void SetBluePolice(Graphics::Motion* motion) { m_bluePolice = motion; };

	void SetPathManager(GameObject* val) { m_pathManager = val; }

	void SetDirection(MathEngine::Vector2 val) { m_direction = val; }
	void SetAudioSource(AudioSource* audioSource) { m_audioSource = audioSource; };

	void SetIsInterrogated(bool val) { m_isInterrogated = val; }

private:
	void ChangeState(State nextState);

	bool IsRecognizePlayer();
	bool IsCollision();

	State m_curState;
	FSM* m_FSM;
	AudioSource* m_audioSource;

	Transform* m_playerTransform;
	Transform* m_policeTrasnform;
	Graphics::Motion* m_police;
	Graphics::Motion* m_redPolice;
	Graphics::Motion* m_bluePolice;

	GameObject* m_pathManager;

	int m_index;
	float m_time;
	int m_spriteIndex;

	MathEngine::Vector2 m_preDirection;
	MathEngine::Vector2 m_direction;

	MathEngine::Vector2 m_policeStation;
	std::string m_mapDataPath;

	// �ɹ� �޴� ��
	bool m_isInterrogated;
	float m_interrogatedTime = 0.0f;

	// �ν� ����
	MathEngine::Vector2 m_recognizeRange;

	// ���� ���
	std::vector<MathEngine::Vector2> m_route;

	// ��ã�� �˰���
	Algorithm::PathFinding* m_pathfind;

	// �ӵ�
	float m_speed;

	friend class PoliceIdleState;
	friend class PoliceChasingState;
	friend class PoliceCollisionState;
	friend class PathFindRenderer;
};